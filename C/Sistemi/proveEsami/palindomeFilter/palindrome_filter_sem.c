#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <semaphore.h>
#include <stdbool.h>
/*
Creare un programma che riconosca le parole palindrome in un pool di parole prese da un file di testo che verrà dato in input al programma
Il main thread creerà 3 thread chiamati R,P,W.
R dovrà inserire la parola nella struttura dati condivisa
P dovrà capire se la parola nel buffer è palindroma
W dovrà stampare a video la parola palindroma
Usare e capire dove inserire i mutex.
*/
#define BUFFER_SIZE 100

/*
 name = c|i|a|o| \n|\0|
 0 1 2 3  4  5 -> n - 2 -> = \0
 strspn(name, '\n');
*/

typedef struct thread_shared_data
{
    char buffer[BUFFER_SIZE];
    char name_file[20];
    pthread_mutex_t buffer_mutex;
    bool done;
    sem_t sem_R, sem_P, sem_W;

} thread_shared;

void *thread_function_R(void *args)
{
    // printf("Thread_R\n");
    thread_shared *shared = (thread_shared *)args;
    FILE *file_text;
    printf("%s\n", shared->name_file);
    if ((file_text = fopen(shared->name_file, "r")) == NULL)
    {
        perror("Errore nell'apertura del file\n");
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    while (1)
    {
        // sem_R = 1
        sem_wait(&shared->sem_R); // sem_R = 0
        // printf("[R]sono nel ciclo\n");
        pthread_mutex_lock(&shared->buffer_mutex);
        // printf("[R]semafori ok\n");
        if (fgets(buffer, BUFFER_SIZE, file_text) == NULL)
        {
            printf("[R] Concludo l'esecuzione\n");
            shared->done = true; // Fine del file
            pthread_mutex_unlock(&shared->buffer_mutex);
            sem_post(&shared->sem_P); // Sveglio P per far terminare il ciclo
            break;
        }
        // Togliamo il carattere newline dalla stringa
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(shared->buffer, buffer);
        printf("[R] %s\n", shared->buffer);
        pthread_mutex_unlock(&shared->buffer_mutex);
        printf("[R] Sveglio [P]\n");
        sem_post(&shared->sem_P); // sem_P = 1
    }

    fclose(file_text);

    return NULL;
}
void *thread_function_W(void *args)
{
    thread_shared *shared = (thread_shared *)args;
    while (1)
    {
        // stampo e passo la palla a R
        sem_wait(&shared->sem_W);
        // printf("[W]\n");
        pthread_mutex_lock(&shared->buffer_mutex);
        if (shared->done)
        {
            printf("[W] Concludo l'esecuzione\n");
            pthread_mutex_unlock(&shared->buffer_mutex);
            return NULL; // Termina il thread W
        }
        printf("[W] La parola palindroma è = %s\n", shared->buffer);
        pthread_mutex_unlock(&shared->buffer_mutex);
        sem_post(&shared->sem_R);
        // passo la palla a R
    }
    return NULL;
}

void *thread_function_P(void *args)
{
    thread_shared *shared = (thread_shared *)args;
    // controllo la palindromicità
    // passo la palla a W se è palindroma altrimenti ad R
    while (1)
    {
        sem_wait(&shared->sem_P); // sem_P = 0
        pthread_mutex_lock(&shared->buffer_mutex);
        bool flag = true;
        // sem_P = 1
        //  a | c | c | a => strlen > 4 - 1 = 3
        int tail = strlen(shared->buffer) - 1;
        printf("[P] Controllo se la parola è palindroma\n");
        for (int i = 0; i < strlen(shared->buffer) / 2; i++)
        {
            if (shared->buffer[i] != shared->buffer[tail - i])
            {
                // Caso 1 la parola non è palindroma
                printf("La parola non è palindroma\n");
                pthread_mutex_unlock(&shared->buffer_mutex);
                sem_post(&shared->sem_R);
                flag = false;
                break;
                // torna a palla a R
            }
        }
        if (flag)
        {
            // Caso 2 la parola è palindroma
            printf("[P] Sveglio [W]\n");
            pthread_mutex_unlock(&shared->buffer_mutex);
            sem_post(&shared->sem_W);
        }

        if (shared->done)
        {
            printf("[P] Concludo l'esecuzione\n");
            pthread_mutex_unlock(&shared->buffer_mutex);
            sem_post(&shared->sem_W);
            break;
            // Termina il thread P
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        perror("Errore nell'inserimento degli input\n");
        exit(EXIT_FAILURE);
    }

    // allocazione dinamica di un puntatore di shared_data
    printf("Alloco la struttura condivisa\n");
    thread_shared *shared_data = (thread_shared *)malloc(sizeof(thread_shared));
    strcpy(shared_data->name_file, argv[1]);
    printf("%s\n", shared_data->name_file);
    shared_data->done = false;
    // Inizializzazione del mutex
    if (pthread_mutex_init(&shared_data->buffer_mutex, NULL) != 0)
    {
        perror("Errore nella creazione del mutex\n");
        exit(EXIT_FAILURE);
    }
    // Inizializzo il semaforo di R
    if (sem_init(&shared_data->sem_R, 0, 1) != 0)
    {
        perror("Errore nella creazione del mutex\n");
        exit(EXIT_FAILURE);
    }
    // Inizializzo il semaforo di P
    if (sem_init(&shared_data->sem_P, 0, 0) != 0)
    {
        perror("Errore nella creazione del mutex\n");
        exit(EXIT_FAILURE);
    }
    // Inizializzo il semaforo di W
    if (sem_init(&shared_data->sem_W, 0, 0) != 0)
    {
        perror("Errore nella creazione del mutex\n");
        exit(EXIT_FAILURE);
    }

    // Creazione dei thread
    printf("Alloco i thread\n");
    pthread_t thread_W, thread_R, thread_P;
    pthread_create(&thread_R, NULL, thread_function_R, shared_data);
    pthread_create(&thread_P, NULL, thread_function_P, shared_data);
    pthread_create(&thread_W, NULL, thread_function_W, shared_data);

    //Dealloco le risorse utilizzate
    pthread_join(thread_R, NULL);
    sem_destroy(&shared_data->sem_R);
    pthread_join(thread_P, NULL);
    sem_destroy(&shared_data->sem_P);
    pthread_join(thread_W, NULL);
    sem_destroy(&shared_data->sem_W);
    pthread_mutex_destroy(&shared_data->buffer_mutex);
    free(shared_data);

    //Concludo il programma con un SUCCESS
    printf("Programma terminato correttamente ! \n");
    exit(EXIT_SUCCESS);
}