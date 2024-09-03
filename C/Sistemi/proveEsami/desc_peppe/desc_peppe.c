#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>
#include <semaphore.h>



/* COMPITO 29 Luglio 2024
SPIEGAZIONE: modello 1 master - N slave
Il main thread (master) legge ogni riga dal file di input, la mette nel buffer condiviso e risveglia il thread corrispondente alla chiave (slave)
Il thread slave decifra la riga e la scrive nel buffer condiviso, risvegliando il main thread che stamperà poi la riga decifrata
Subito dopo il thread si blocca nuovamente in attesa di essere risvegliato dal main thread
*/


#define BUFFER_SIZE 1000
#define MAX_KEYS 100

//Come prima cosa distinguiamo le strutture condivise da quelle singole rispetto ai thread.

// Struttura dati condivisa tra i thread
typedef struct {
    char buffer[BUFFER_SIZE];
    sem_t* main_sem;
} shared_data_t;


// Struttura dati specifica per ogni thread
typedef struct {
    char key[26];
    // Campo che non è strettamente necessario ma utile per far stampare al thread il suo numero di chiave in modo indipendente dal main thread
    int key_number; 
    shared_data_t* shared;
    sem_t sem; //semaforo
} thread_data_t;


//funzione per decriptare la linea
void decrypt_line(char* plaintext, char* ciphertext, char* key){
    for(int i = 0; i < strlen(ciphertext); i++){
        if(ciphertext[i] >= 'a' && ciphertext[i] <= 'z'){
            plaintext[i] = key[ciphertext[i] - 'a'];
        }
        else {
            plaintext[i] = ciphertext[i]; // punteggiatura, spazi, ecc.
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
//funzione del thread
void* thread_loop(void* arg){
    thread_data_t* data = (thread_data_t*) arg;
    printf("[K%d] Chiave assegnata: %s\n", data->key_number, data->key);
    while(1){
        // Ogni thread, poiche il semaforo è inizializzato a 0, si blocca non appena entra e rimane in attesa di essere risvegliato dal main thread al momento opportuno
        // IMPORTANTE: la down su semaforo uguale a 0 non viene completata ed il thread si blocca 
        // Quando il main_thread fa sem_post, il thread si sblocca ed il valore del semaforo è 0
        sem_wait(&data->sem);

        printf("[K%d] Sto decifrando la frase di %d caratteri passata dal main thread\n", data->key_number, strlen(data->shared->buffer));
        char plaintext_line[BUFFER_SIZE];
        decrypt_line(plaintext_line, data->shared->buffer, data->key);
        strcpy(data->shared->buffer, plaintext_line);


        // Quando il thread finisce di decifare la riga, risveglia il main thread
        sem_post(data->shared->main_sem);
    }
    return NULL;
}

int load_keys(char keys[MAX_KEYS][26], const char* keys_filename){
    FILE* keys_file = fopen(keys_filename, "r");
    // fgets include lo /n ed aggiunge il terminatore di stringa \0 +2
    char current_key[28];
    int N = 0;
    while(fgets(current_key, 28, keys_file)){
        current_key[26] = '\0';
        strncpy(keys[N], current_key, 26);
        N++;
    }
    fclose(keys_file);
    return N;
}


void initialize_thread_data(thread_data_t* data, shared_data_t* shared, const char* key, int key_number){
    data->shared = shared;
    strncpy(data->key, key, 26);
    data->key[26] = '\0';
    data->key_number = key_number;
    // Il semaforo è inizializzato a 0, quindi il thread si blocca non appena entra
    sem_init(&data->sem, 0, 0);
}

void parse_line(char* line, int* key_number, char* ciphertext){
    // Copia il numero della chiave in key_number
    sscanf(line, "%d: ", key_number);
    // Copia la stringa a partire dal 3° carattere (dopo il numero e i due punti)
    strcpy(ciphertext, line + 3);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
}

void process_ciphertext(const char* ciphertext_filename, const char* plaintext_filename, shared_data_t* shared, thread_data_t* thread_data) {
    FILE* ciphertext_file = fopen(ciphertext_filename, "r");
    FILE* plaintext_file = plaintext_filename ? fopen(plaintext_filename, "w") : NULL;
    char line[BUFFER_SIZE];
    while(fgets(line, BUFFER_SIZE, ciphertext_file)){
        int key_number;
        char ciphertext[BUFFER_SIZE];
        parse_line(line, &key_number, ciphertext);
        strncpy(shared->buffer, ciphertext, BUFFER_SIZE);
        printf("[M] La riga '%s' deve essere decifrata con la chiave n.%d\n", shared->buffer, key_number);
            
        // Risveglia il thread che gestisce questa chiave
        // -1 perché indicizziamo da 0: la prima chiave è la chiave 0
        sem_post(&thread_data[key_number-1].sem);
        // Aspetta che il thread abbia finito
        sem_wait(shared->main_sem);
            
        // Stampa il risultato a schermo
        printf("[M] La riga è stata decifrata in: %s\n", shared->buffer);
        if(plaintext_file){
            fprintf(plaintext_file, "%s\n", shared->buffer);
        }
    }

    fclose(ciphertext_file);
    if (plaintext_file) {
        fclose(plaintext_file);
    }

}

int main(int argc, char** argv){

    if(argc < 3 || argc > 4){
        fprintf(stderr, "Usage: %s <keys-file> <ciphertext-input-file> [plaintext-input-file]\n", argv[0]);
        return EXIT_FAILURE;
    }


    // Il numero di chiavi non si conosce a priori, potenzialemente potrebbero essere anche 26!. Per semplicità assumiamo che sia minore di MAX_KEYS
    char keys[MAX_KEYS][26];
    int N = load_keys(keys, argv[1]);
    printf("[M] Trovate %d chiavi: creo i thread K-i necessari\n", N);


    shared_data_t shared;
    sem_t main_sem;
    sem_init(&main_sem, 0, 0);
    shared.main_sem = &main_sem;

    pthread_t* threads = malloc(N * sizeof(pthread_t));
    thread_data_t* thread_data = malloc(N * sizeof(thread_data_t));

    for(int i = 0; i < N; i++){
        initialize_thread_data(&thread_data[i], &shared, keys[i], i+1);
        pthread_create(&threads[i], NULL, thread_loop, &thread_data[i]);
    }

    process_ciphertext(argv[2], argc == 4 ? argv[3] : NULL, &shared, thread_data);

    for(int i = 0; i < N; i++){
        // Non è molto elegante cancellare i thread, sarebbe meglio usare un flag per far terminare il ciclo while
        pthread_cancel(threads[i]);
        sem_destroy(&thread_data[i].sem);
    }

    free(threads);
    free(thread_data);
    sem_destroy(&main_sem);


    return EXIT_SUCCESS;
}