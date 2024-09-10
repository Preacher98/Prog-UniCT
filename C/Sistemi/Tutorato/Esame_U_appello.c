#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<semaphore.h>

#define KEYS_SIZE 30
#define BUFFER_SIZE 100

typedef struct shared_data{
    char buffer[BUFFER_SIZE];
    sem_t buff_sem; //Ha la funzione di gestire l'accesso al buffer
    int exit;
    //semafori
}shared_data_t;

typedef struct thread_data{
    char keys[KEYS_SIZE];
    int index;
    shared_data_t *data;
    //semafori
    sem_t thread_sem; //da inizializzare e bloccare
}thread_data_t;

void *thread_function(void *args){
    thread_data_t *dt=(thread_data_t*)args;
    printf("[K%d] chiave assegnata al: %s\n", dt->index, dt->keys);
    //Impostare i semafori per farli entrare in sleep e risvegliarli
    //inizialmente tutti i thread sono bloccati, sarà il main a svegliarli, per farlo necessario semaforo gia a 0 cosi è bloccante 
    
    return NULL;
}



int main(int argc, char **argv){
    if (argc <3)
    {
        perror("Errore nell'inserimento dei parametri\n");
        exit(EXIT_FAILURE);
    }
    
    char *keys_input_filename = argv[1];
    char *cifar_input_filename = argv[2];
    char *ouput_filename = argc > 3 ? argv[3] : "output.txt";
    //Serve un semaforo ancehe per il main thread ovvero il main
    printf("[M]Leggo il file delle chiavi\n");
    //Prima della creazione dei thread dobbiamo capire quante chiavi abbiamo a nostra disposizione
    FILE* key_fp = fopen(keys_input_filename,"r");
    if(key_fp == NULL){
        perror("Errore nel recuperare le chiavi\n");
        exit(EXIT_FAILURE);
    }
    
    int num_keys = 0;
    while(!feof(key_fp))
    {
        if (fgetc(key_fp) == "\n")
        {
           num_keys++;
        }
        
    }
    fseek(key_fp, 0, SEEK_SET);

    printf("[M] Trovate %d chiavi nel file, creiamo k-1 thread: \n",num_keys);
    //creazione delle strutture dati di supporto, "data" come struttura condivisa, data_array sarà l'array di puntatori per i thread
    shared_data_t *data = (shared_data_t*)malloc(sizeof(shared_data_t));
    //ogni elemento contiene un puntatore alla strutura che passeremo al singolo thread
    data->exit=0;
    thread_data_t **thread_data_array = (thread_data_t **) malloc(sizeof(thread_data_t*)*num_keys);
    char key_buffer[KEYS_SIZE];
    int j = 0;
    //Costruzione degli elementi da passare al thread
    while (fgets(key_buffer, KEYS_SIZE, key_fp) != NULL)
    {
    
        thread_data_t *item = (thread_data_t*) malloc(sizeof(thread_data_t));
        item->data = data; //data è la struttura condivisa
        item->index = j;
        strcpy(item->keys, key_buffer);
        printf("%s\n",item->keys);

        //inizializzazione del semaforo con sem_init da impostare a 0

        thread_data_array[j]=item;
        j++;
        
    }
    //I semafori in questo contesto devono essere inizializzati prima della creazione del thread per risultare bloccanti.
    printf("Creazione dei thread\n");
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t));
    for (int i = 0; i < num_keys; i++)
    {
       if(pthread_create(threads[i], NULL, thread_function, thread_data_array[i]) < 0){
        perror("Errore nella creazione del thread\n");
        exit(EXIT_FAILURE);
       }
    }
    
    //Assegnazione testo ai thread
    printf("[M] Processo il file cifrato \n");
    FILE* cif_fp = fopen(cifar_input_filename, "r");
    if (cif_fp == NULL)
    {
        perror("Errore nell'apertura dei file cifrati\n");
        exit(EXIT_FAILURE);
    }
    
    //incremento e decremento dei semafori quando si copia il testo nel buffer




    for (int i = 0; i < num_keys; i++)
    {
        pthread_join(threads[i],NULL);
    }
    


}



//funzione che permette di separare il testo in due parti, la prima parte contiene l'indice del thread da risvegliare, la seconda il testo da decifrare
//ricordarsi di deallocare tutte le strutture dinamiche utilizzate e anche di chiudere tutti i file
//Con i MUTEX invece si devono bloccare subito dopo essere stati creati