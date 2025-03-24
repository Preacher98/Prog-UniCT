#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <ctype.h>
#include <semaphore.h>

#define BUFFER_SIZE 100
#define ALPH_SIZE 26

typedef struct shared_struct_thread
{
    char frase_Da_scoprire[BUFFER_SIZE];
    char carattere_inserito;
    int num_player;
    int lettere_uscite[ALPH_SIZE]; // Fungerà da bitmap per mappare le lettere uscite
    bool fine_partita;
    int *punteggi;
    sem_t turn_sem;
    // mutex da inserire

} tabellone;

typedef struct local_struct_thread_data
{
    int id;
    tabellone *share;
    pthread_mutex_t read_m, write_m;

} player_t;

FILE *apertura_file(char *filename);
void shuffle(int *index, int size_ind);
void swap(int *source, int *dest);
int choose_phrase(int *array_index, int *size);
void oscurare_frase(char *frase_chiara, char *frase_oscurata);
void reset_Alph(int *lettere_uscite);
int frase_completata_T(char *frase_oscurata);
int controllo_frase_carattere(char *frase_oscurata, char *frase_chiara, char lettera);
char genera_carattere(int *lettere_uscite);

// Funzione dei thread player
void *player_function(void *args)
{
    player_t *player = (player_t *)args;
    tabellone *tabella = (tabellone *)player->share;
    printf("[%d] Sono sveglio\n", player->id);
    sem_post(&tabella->turn_sem);
   
    
    while (!tabella->fine_partita)
    {
    
        pthread_mutex_lock(&player->read_m); 
        tabella->carattere_inserito = genera_carattere(tabella->lettere_uscite);
        printf("\t[G%d] chiamo la lettera %c\n",player->id,tabella->carattere_inserito);
        
        pthread_mutex_unlock(&player->write_m);
    }
    
    printf("[G%d] Mi sto chiudendo correttamente\n",player->id);
    return NULL;
}

int main(int argc, char **argv)
{
     srand(time(0));
    // Int n_partite, int n_giocatori char *filename
    if (argc != 4)
    {
        perror("Errore nell'inserimento dei parametri iniziali ! \n");
        exit(EXIT_FAILURE);
    }

    int n_partite = 0;
    int n_giocatori = 0;
    char filename[30];

    n_partite = atoi(argv[1]);
    n_giocatori = atoi(argv[2]);
    strcpy(filename, argv[3]);
    FILE *open_file = apertura_file(filename);
    int fd_file = fileno(open_file);

    char buffer[BUFFER_SIZE];
    int num_frasi = 0;
    // conto il numero di frasi
    while (!feof(open_file))
    {
        fgets(buffer, BUFFER_SIZE, open_file);
        // printf("%d)%s\n",num_frasi,buffer);
        num_frasi++;
    }
    // Controllo condizioni necessarie per la partita
    if (num_frasi < n_partite)
    {
        printf("Frasi insufficienti per gestire il numero di partite \n");
        exit(EXIT_FAILURE);
    }
    // Creo il puntatore per size e l'indice delle frasi inizializzandoli
    int *size = &num_frasi;
    int index_phrase[num_frasi];
    for (int i = 0; i < num_frasi; i++)
    {
        index_phrase[i] = i;
    }
    shuffle(index_phrase, num_frasi);

    // Creazione dei thread giocatori in base al numero di n_giocatori e del tabellone
    tabellone *tabella = (tabellone *)malloc(sizeof(tabellone));
    tabella->num_player = n_giocatori;
    tabella->punteggi = calloc(n_giocatori, sizeof(int));
    tabella->fine_partita = false;

    if (sem_init(&tabella->turn_sem, 0, 0) < 0)
    {
        perror("Errore nell'inizializzazione del semaforo init\n");
        exit(EXIT_FAILURE);
    }

    player_t **player_Arr = (player_t **)malloc(sizeof(player_t*) * n_giocatori);
    pthread_t *thread_p = (pthread_t *)malloc(sizeof(pthread_t) * n_giocatori);

    for (int i = 0; i < n_giocatori; i++)
    {
        player_t *player = (player_t *)malloc(sizeof(player_t));
        player->id = i;
        player->share = tabella;

        // Dichiarazione dei thread
        // inserire inizializzazione dei semafori
        if (pthread_mutex_init(&player->read_m, NULL) < 0)
        {
            perror("Errore nell'inizializzazione del mutex read\n");
            exit(EXIT_FAILURE);
        }
        pthread_mutex_lock(&player->read_m);
        if (pthread_mutex_init(&player->write_m, NULL) < 0)
        {
            perror("Errore nell'inizializzazione del mutex write\n");
            exit(EXIT_FAILURE);
        }
        pthread_mutex_lock(&player->write_m);

        if (pthread_create(&thread_p[i], NULL, player_function, player) < 0)
        {
            perror("Errore nella creazione dei thread\n");
            exit(EXIT_FAILURE);
        }
        player_Arr[i]=player;
    }

        //Il main entra in wait e ogni thread lancia la post per tornare sul main
        for (int i = 0; i < n_giocatori; i++)
        {
            sem_wait(&tabella->turn_sem);
        }
        printf("[M] Ho aspettato tutti i thread\n");
    
    //Iniziano le partite
    for (int i = 0; i < n_partite; i++) {

            //scelta della frase e occultamento
            int frase = choose_phrase(index_phrase,size);
            int indice = 0;
            fseek(open_file, 0, SEEK_SET);
            while (frase != indice)
            {
                fgets(buffer, BUFFER_SIZE, open_file);
                //printf("[M] %s\n",buffer);
                indice++;
            }
        printf("\t[M] Turno %d\n",i);
        printf("[M] %s\n",buffer); 
        strcpy(tabella->frase_Da_scoprire,buffer);  
        oscurare_frase(buffer,tabella->frase_Da_scoprire);
        printf("[M] %s\n",tabella->frase_Da_scoprire);
        
        int num=0;
        //printf("[M] %s",tabella->frase_Da_scoprire);
        int partite = 0;

        //Creazione turno
        while (frase_completata_T(tabella->frase_Da_scoprire) != 1){  
            //printf("[M] while 2"); 
            int turno_giocatore = 0;
            while (turno_giocatore < n_giocatori && !frase_completata_T(tabella->frase_Da_scoprire)) {
                //printf("[M] while 3");
                printf("[M] Frase oscurata : %s",tabella->frase_Da_scoprire);
                printf("[M] Turno del giocatore G[%d]\n",turno_giocatore);
                pthread_mutex_unlock(&player_Arr[turno_giocatore]->read_m);
               
                pthread_mutex_lock(&player_Arr[turno_giocatore]->write_m);
                num = controllo_frase_carattere(tabella->frase_Da_scoprire, buffer, tabella->carattere_inserito);
                printf("[M] Il giocatore %d, ha indovinato %d lettere ! \n",turno_giocatore, num);
                player_Arr[turno_giocatore]->share->punteggi[turno_giocatore] += num * 100;
                printf("[M] giocatore %d punteggio = %d\n", turno_giocatore, player_Arr[turno_giocatore]->share->punteggi[turno_giocatore]);
                
                turno_giocatore++;
            } 
            

        }
        printf("[M] La frase è stata completata !\n");
        reset_Alph(tabella->lettere_uscite);
        partite++;
    }
    tabella->fine_partita = true;

        for (int i = 0; i < n_giocatori; i++)
        {
            pthread_mutex_unlock(&player_Arr[i]->read_m);
            pthread_join(thread_p[i], NULL);
            pthread_mutex_destroy(&player_Arr[i]->write_m);
            pthread_mutex_destroy(&player_Arr[i]->read_m);
            free(player_Arr[i]);
        }
        free(tabella);
        // chiusura file e programma
        fclose(open_file);
        return 0;
    
}

FILE *apertura_file(char *filename)
{

    FILE *open_file = fopen(filename, "r");
    if (open_file == NULL)
    {
        perror("Errore nell'apertura del file\n");
        exit(EXIT_FAILURE);
    }
    return open_file;
}

void shuffle(int *index, int size_ind) {
    for (int i = 0; i < size_ind; i++)
    {
        int r = rand() % size_ind;
        int temp = index[r];
        index[r] = index[i];
        index[i] = temp;
    }
}

void swap(int *source, int *dest)
{
    int temp = *source;
    *source = *dest;
    *dest = temp;
}

int choose_phrase(int *array_index, int *size)
{
    int r = rand() % (*size);
    int frase_scelta = array_index[r];
    int dim = *size;
    swap(&array_index[r], &array_index[dim - 1]);
    (*size)--;
    //printf("%d\n", *size);
    return frase_scelta;
}

void oscurare_frase(char *frase_chiara, char *frase_oscurata){

    for (int i = 0; i < strlen(frase_chiara); i++)
    {
        frase_chiara[i]=tolower(frase_chiara[i]);
        if (frase_chiara[i] >= 'a' && frase_chiara[i]<= 'z')
        {
            
            frase_oscurata[i] = '_';
        }else
        {
            frase_oscurata[i] = frase_chiara[i];
        }
        
    }
    //printf("%s \n phrase: %s\n",frase_chiara,frase_oscurata);   
}

void reset_Alph(int *lettere_uscite){
    for (int i = 0; i < ALPH_SIZE; i++)
    {
        lettere_uscite[i] = 0;
    }   
}

int frase_completata_T(char *frase_oscurata){
    
    if (strchr(frase_oscurata,'_') == NULL)
    {
        return 1;
    }
    
    return 0;
}

int controllo_frase_carattere(char *frase_oscurata, char *frase_chiara, char lettera){

    int lettere_giuste = 0;
    for (int i = 0; i < strlen(frase_chiara); i++)
    {
        if (frase_chiara[i] == lettera)
        {
            frase_oscurata[i]=lettera;
            lettere_giuste++;
        }
    }   
    return lettere_giuste;
}

char genera_carattere(int *lettere_uscite){
    
    char car = 'a' + (rand()%ALPH_SIZE);   
    
    if (lettere_uscite[car - 'a'] == 1)
    {
        car = genera_carattere(lettere_uscite);
    }
    
    lettere_uscite[car - 'a'] = 1;
    return car;
}

