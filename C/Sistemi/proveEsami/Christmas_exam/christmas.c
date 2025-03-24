#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<semaphore.h>


typedef enum {BUONO,CATTIVO}comport_t;

#define TYPE_SIZE 40

typedef struct christmas_shared_struct
{
    char *nome_bambino;
    char *nome_regalo;
    comport_t comportamento;
    int costo_regalo;
    //altri flag
    int turno;
    //mutex
    pthread_mutex_t shared_mutex;
    //le cond_var servono nella struttura condivisa
    pthread_cond_t cond_contab;
    pthread_cond_t cond_produt;
    pthread_cond_t cond_indag;
    pthread_cond_t cond_babbo;
    pthread_cond_t *cond_smist;
}shared_struct;

typedef struct elfo_smistatore
{
    char nome_lettera[TYPE_SIZE];
    char nome_bambino[TYPE_SIZE];
    char nome_regalo[TYPE_SIZE];
    shared_struct *shared;
    int id;
    //Altre variabili ?
}Elf_smist;

typedef struct babbo_natale //Funge da coordinatore ?
{
    shared_struct *shared;
    // mi serve questa struttura ?
}Santa_klaus;

typedef struct elfo_indagatore
{
    char nome_file[TYPE_SIZE];
    char nome_bimbo[TYPE_SIZE];
    comport_t comportamento;
    shared_struct *shared;
}elf_ind;

typedef struct elfo_produttore
{
    char nome_file[TYPE_SIZE];
    char nome_regalo[TYPE_SIZE];
    int costo;
    shared_struct *shared;
}elf_prod;

typedef struct elfo_contabile
{
    int numero_buoni;
    int numero_cattivi;
    long int bilancio_totale;
    shared_struct *shared;
}elf_cont;

//Thread Function
void *smistatori_function(void *args) {
    Elf_smist *elf_sm = (Elf_smist *) args;
    //printf("[ES%d] Mi sono svegliato ! \n", elf_sm->id);
    pthread_mutex_lock(&elf_sm->shared->shared_mutex);
    printf("[ES%d] sono nel lock! \n", elf_sm->id);
    while (elf_sm->shared->turno != 1)
    {
        //printf("[ES%d] sono nel lock! \n", elf_sm->id);
        pthread_cond_wait(&elf_sm->shared->cond_smist[elf_sm->id], &elf_sm->shared->shared_mutex);
    }
        printf("[ES%d] Sono pronto a leggere la lettera %s ! \n", elf_sm->id, elf_sm->nome_lettera);
        pthread_mutex_unlock(&elf_sm->shared->shared_mutex);
    
    return NULL;
}

//Funzione di babbo natale
void *santaklaus_function(void *args){
    Santa_klaus *babbo = (Santa_klaus *) args;
    printf("[Babbo] Oh-Oh-Oh sono pronto a consegnare regali !\n");
    printf("[Babbo] Svegli gli smistatori\n");
    pthread_mutex_lock(&babbo->shared->shared_mutex);
    babbo->shared->turno= 1;
    printf("[Babbo] Imposto ad %d\n", babbo->shared->turno);
    for (int i = 0; i < 3; i++)
    {
        pthread_cond_signal(&babbo->shared->cond_smist[i]);

    }
    
    pthread_mutex_unlock(&babbo->shared->shared_mutex);
    return NULL;
}

void *production_function(void *args){
    elf_prod *production = (elf_prod *) args;
    printf("[EP] Ehilà sono pronto a produrre giocattoli ! \n");
    return NULL;
}

void *contabile_function(void *args){
    elf_cont *contabile = (elf_cont *) args;
    printf("[EC] Sono pronto a gestire la contabilità ! \n");
    return NULL;
}

void *indagatore_function(void *args){
    elf_ind *indagatore = (elf_ind *) args;
    printf("[EI] Sono pronto a scoprire chi è buono e chi non lo è ! \n");
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 6)
    {
       perror("Errore nell'inserimento dei dati\n");
       exit(EXIT_FAILURE);
    }
    int n_smistatori = argc - 3; 
    //dichiarare struct condivisa
    shared_struct *shared = (shared_struct *) malloc(sizeof(shared_struct));
    //dichiarazione elfi smistatori e corrispettiva struct
    printf("%d smsitatori\n",n_smistatori);
    pthread_t *smistatori = (pthread_t*) malloc(sizeof(pthread_t)*n_smistatori);
    Elf_smist *elf_sm = (Elf_smist *) malloc(sizeof(Elf_smist)*n_smistatori);
    shared->turno = 0;
    pthread_mutex_init(&shared->shared_mutex, NULL);
    shared->cond_smist = (pthread_cond_t *) malloc(sizeof(pthread_cond_t)*n_smistatori);

    for (int i = 0; i < n_smistatori; i++)
    {
        elf_sm[i].shared = shared;
        elf_sm[i].id = i;
        pthread_cond_init(&shared->cond_smist[i],NULL);
        strcpy(elf_sm[i].nome_lettera, argv[3+i]);
        //inizializzazione di una variabile cond per smistatore
        if(pthread_create(&smistatori[i], NULL, smistatori_function, &elf_sm[i]) < 0)
        {
            perror("Errore nella creazione dei thread! \n");
            exit(EXIT_FAILURE);
        }
    }
    //Dichiarazione altri thread
    pthread_t babbo_natale, elf_pr, elf_ct, elf_in;
    Santa_klaus *babbo_nata = (Santa_klaus *) malloc(sizeof(Santa_klaus));
    babbo_nata->shared = shared;
    elf_ind *elf_indag = (elf_ind *) malloc(sizeof(elf_ind));
    elf_prod *prod_elf = (elf_prod *) malloc(sizeof(elf_prod));
    elf_cont *cont_elf = (elf_cont *) malloc(sizeof(elf_cont));
    
    //Creazione dei thread dei vari worker
    if(pthread_create(&babbo_natale, NULL, santaklaus_function, babbo_nata) < 0)
        {
            perror("Errore nella creazione dei thread! \n");
            exit(EXIT_FAILURE);
        }
    if(pthread_create(&elf_pr, NULL, production_function, prod_elf) < 0)
        {
            perror("Errore nella creazione dei thread! \n");
            exit(EXIT_FAILURE);
        }
    if(pthread_create(&elf_ct, NULL, contabile_function, cont_elf) < 0)
        {
            perror("Errore nella creazione dei thread! \n");
            exit(EXIT_FAILURE);
        }

    if(pthread_create(&elf_in, NULL, indagatore_function, elf_indag) < 0)
        {
            perror("Errore nella creazione dei thread! \n");
            exit(EXIT_FAILURE);
        }


    //Join e chiusura del programma e deallocazione
    for (int i = 0; i < n_smistatori; i++)
    {
        pthread_join(smistatori[i], NULL);
    }

    //pthread_t babbo_natale, elf_pr, elf_ct, elf_in;
    pthread_join(babbo_natale, NULL);
    pthread_join(elf_pr, NULL);
    pthread_join(elf_ct, NULL);
    pthread_join(elf_in, NULL);
    
    
    return 0;

}