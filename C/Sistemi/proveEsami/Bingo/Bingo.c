#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<semaphore.h>

#define ROWS 3
#define COL 5
#define MAX_NUM_EX 75

//Struct card per facilitare la creazione di m matrici
typedef struct card_matrix_struct
{
    int **card_matrix;
}card_t;

typedef struct shared_bingo_struct
{
    card_t *shared_card;
    int numero_estratto;
    int *num_usciti;
    int n_tot;
    pthread_t bingo, cinquina;
    sem_t main_sem;
    pthread_mutex_t card_mutex;
    //inserire semafori e bingo e cinquina
    
}gestione_condivisa;

//Struct condivisa
typedef struct player_struct_bingo
{
    int id;
    int m_card;
    card_t *local_card;
    gestione_condivisa *condivisione;
    sem_t player_sem;

}player_str;


void popola_card(card_t *card_player);
int genera_rand(int *array);
void stampa_matrice(int **matrix);
int estrai_numero(int *num_estratti, int n_tot);
void controlla_card(player_str *player_dati);

//Struct del player
void *player_function(void *args){
    player_str *player_dati = (player_str *) args;
    
    sem_wait(&player_dati->player_sem);
    printf("[P%d] Sono pronto a giocare !\n",player_dati->id);
    sem_post(&player_dati->condivisione->main_sem);
    sem_wait(&player_dati->player_sem);
    
    for (int i = 0; i < player_dati->m_card; i++)
    {
        pthread_mutex_lock(&player_dati->condivisione->card_mutex);
        player_dati->local_card[i] = *player_dati->condivisione->shared_card;
        printf("[P%d] \n",player_dati->id);
        stampa_matrice(player_dati->local_card[i].card_matrix);
        printf("\n");
        pthread_mutex_unlock(&player_dati->condivisione->card_mutex);
        sem_post(&player_dati->condivisione->main_sem);
        sem_wait(&player_dati->player_sem);
    }
    //sem_post(&player_dati->condivisione->main_sem);
    while (!player_dati->condivisione->bingo)
    {
        
        printf("[P%d] Ho visto il numero %d\n", player_dati->id, player_dati->condivisione->numero_estratto);
        sem_post(&player_dati->condivisione->main_sem);
        sem_wait(&player_dati->player_sem);
        if (player_dati->condivisione->n_tot ==21)
        {
           break;
        }
    }
    
    

    return NULL;
}

int main(int argc, char **argv){
    
    
    srand(time(0));

    if (argc != 3)
    {
        perror("Errore nell'inserimento dei parametri\n");
        exit(EXIT_FAILURE);
    }

    int n_player = atoi(argv[1]);
    int m_card = atoi(argv[2]);
    printf("[D] Ci sono %d Giocatori ognuno con %d schede\n",n_player,m_card);

    gestione_condivisa *dealer_cond = (gestione_condivisa *)malloc(sizeof(gestione_condivisa));
    dealer_cond->shared_card = (card_t *) calloc(1, sizeof(card_t)); 
    player_str *player_arr = (player_str *) malloc (sizeof(player_str)*n_player);
    pthread_t *player_t = (pthread_t *) malloc(sizeof(pthread_t)*n_player);
    dealer_cond->n_tot=0;
    dealer_cond->numero_estratto = 0;
    dealer_cond->num_usciti = (int *) calloc(MAX_NUM_EX, sizeof(int));
    dealer_cond->bingo = false;
    dealer_cond->cinquina = false;
    //mutex sulla card
    pthread_mutex_init(&dealer_cond->card_mutex, NULL);
    if (sem_init(&dealer_cond->main_sem, 0, 0) != 0)
        {
            perror("Errore nell'inizializzazione del semaforo\n");
            exit(EXIT_FAILURE);
        }

    printf("[D] Sto creando i giocatori\n");
    for (int i = 0; i < n_player; i++)
    {   //inizializzo il player
        player_arr[i].id = i;
        player_arr[i].m_card = m_card;
        player_arr[i].condivisione = dealer_cond;
        player_arr[i].local_card = (card_t *) calloc(m_card,sizeof(card_t));

        if (sem_init(&player_arr[i].player_sem, 0, 0) != 0)
        {
            perror("Errore nell'inizializzazione del semaforo\n");
            exit(EXIT_FAILURE);
        }
        
        
        if (pthread_create(&player_t[i], NULL, player_function, &player_arr[i]) < 0)
        {
            perror("Errore nella creazione del thread ! \n");
            exit(EXIT_FAILURE);
        }
        
        
    }
    
    for (int i = 0; i < n_player; i++)
    {
        sem_post(&player_arr[i].player_sem);
        sem_wait(&dealer_cond->main_sem);
    }
    printf("[D] Tutti i giocatori sono pronti a giocare\n");
    
    //Distribuzione card ai player
    //distribuisci_card
    printf("[D] Sto distribuendo le card\n");
    for (int i = 0; i < n_player; i++)
    {
        for (int j = 0; j < m_card; j++)
        {   
            pthread_mutex_lock(&dealer_cond->card_mutex);
            popola_card(dealer_cond->shared_card);
            pthread_mutex_unlock(&dealer_cond->card_mutex);
            sem_post(&player_arr[i].player_sem);
            sem_wait(&dealer_cond->main_sem);
        }
    }
    //In teoria potrei cancellare tutti i semafori e lasciarne uno solo
    printf("\t[D]****** Siamo pronti a cominciare il gioco del BINGO !! ******\n");
    //sem_post(&dealer_cond->main_sem);
    //fase d gioco (estrazione)
    while (!dealer_cond->bingo) {
        //printf("Sono nel while\n");
       
        dealer_cond->numero_estratto = estrai_numero(dealer_cond->num_usciti, dealer_cond->n_tot);
        printf("[D] Numero estratto = %d\n", dealer_cond->numero_estratto);
        if (dealer_cond->numero_estratto == -1) {
            printf("[D]Sono usciti tutti i numeri ! \n");
            break;
        }

         for (int i = 0; i < n_player; i++){
            sem_post(&player_arr[i].player_sem);
            sem_wait(&dealer_cond->main_sem);
        }


    }
    
    //determinare il vincitore

    //Chiusura programma
    printf("[D] mi accingo a chiudere\n");
    for (int i = 0; i < n_player; i++)
    {
        pthread_join(player_t[i], NULL);
        sem_destroy(&player_arr[i].player_sem);
        
    }
    free(player_arr);
    printf("[D] Ho chiuso tutti i thread correttamente\n");

return 0;
}

int genera_rand(int *array){

    int num = (rand()%75) + 1;

    if (array[num] == 1)
    {
        num = genera_rand(array);
    }
    array[num] = 1;
    return num;
}

void popola_card(card_t *card_player){
    
    int num = 0;
    int array[MAX_NUM_EX] = { 0 };
    //alloco dinamicamente le singole matrici
    card_player->card_matrix = (int**)calloc(ROWS,sizeof(card_t *));
    for (int i = 0; i < COL; i++)
    {
        card_player->card_matrix[i] = (int *)calloc(COL, sizeof(int));
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COL; j++)
        {
           card_player->card_matrix[i][j] = genera_rand(array); 
        }
        
    }
    
}

void stampa_matrice(int **matrix){

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            printf("[%d]",matrix[i][j]);
        }
        printf("\n");
    }
}

int estrai_numero(int *num_estratti, int n_tot){
    //printf("ciao");
    int num = (rand()%75) + 1;

    if (num_estratti[num] == 1)
    {
        num = genera_rand(num_estratti);
        //printf("[estrattore] %d", num);
        n_tot++;
    }
    if (n_tot == 75)
    {
        return -1;
    }
    num_estratti[num] = 1;
    return num;
}

void controlla_card(player_str *player_dati){
    int numeri_presenti = 0;

for (int k = 0; k < player_dati->m_card; k++)
{
    for (int i = 0; i < ROWS; i++)
    {

        for (int j = 0; j < COL; j++)
        {
            /* CONTROLLO CINQUINA */
            if ((player_dati->condivisione->num_usciti[player_dati->local_card[k].card_matrix[i][j]] - 1) == 1 )
            {
                numeri_presenti++;
            }
            
        }
        if (numeri_presenti == 5) {
            pthread_mutex_lock(&player_dati->condivisione->card_mutex);
            player_dati->condivisione->cinquina = pthread_self();
            pthread_mutex_unlock(&player_dati->condivisione->card_mutex);
            
        }
        
        
    }
}       

}