#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define GENERAL_SIZE 50
#define SUPER_SIZE 4096
#define BUFF_SIZE 10

typedef struct shared_data
{
    long int *buffer_file;
    long int size;
    pthread_mutex_t buff_mutex;
    pthread_cond_t cond_stat;
    sem_t sem_elementi;
    bool full;

} shared_d;

typedef struct thread_dir
{
    char pathname[1024];
    long long int size;
    int id;
    shared_d *data_s;
    // altro ?
} dir_t;

typedef struct thread_stat
{
    long int size_temp;
    shared_d *shared;
} stat_t;

void *dir_function(void *args)
{
    dir_t *data = (dir_t *)args;
    DIR *directory;
    printf("[T%d] Sono nel thread\n", data->id);
    directory = opendir(data->pathname);
    if (directory == NULL)
    {
        perror("Errore nell'apertura della directory");
        return NULL;
    }
    struct dirent *entry;
    struct stat statbuf;
    char fullpath[SUPER_SIZE];

    while (1)
    {
        while ((entry = readdir(directory)) != NULL)
        {
            pthread_mutex_lock(&data->data_s->buff_mutex);
            while (data->data_s->full)
            {
                pthread_cond_wait(&data->data_s->cond_stat, &data->data_s->buff_mutex);
            }
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            // Costruisce il percorso completo
            snprintf(fullpath, sizeof(fullpath), "%s/%s", data->pathname, entry->d_name);

            if (stat(fullpath, &statbuf) == -1)
            {
                perror("Errore !\n");
            }
            printf("[T%d] Nome file: %s \n Dimensione: %ld \n", data->id, fullpath, statbuf.st_size);
            // proviamo ad usare il mutex
            int sval = sem_getvalue(&data->data_s->sem_elementi, &sval);
            printf(" sem  = %d ", sval);
            if ( sval == 0)
            {
                data->data_s->full = true;
                pthread_cond_signal(&data->data_s->cond_stat);
                sem_wait(&data->data_s->sem_elementi);
            }
            for (int j = 0; j < BUFF_SIZE; j++)
            {
                if (data->data_s->buffer_file[j] == 0)
                {
                    data->data_s->buffer_file[j] = statbuf.st_size;
                    sem_wait(&data->data_s->sem_elementi);
                    break;
                }
            }
            pthread_mutex_unlock(&data->data_s->buff_mutex);
        }
        data->data_s->full = true;
        //pthread_mutex_unlock(&data->data_s->buff_mutex);
        pthread_cond_signal(&data->data_s->cond_stat);
    }

    return NULL;
}

void *stat_function(void *args)
{
    stat_t *data = (stat_t *)args;

    printf("[STAT] Sono pronto a lavorare ! \n");

    int k = 0;
    while (k < 2)
    {
        pthread_mutex_lock(&data->shared->buff_mutex);
        printf("full = %d\n", data->shared->full);
        while (!data->shared->full)
        {
            pthread_cond_wait(&data->shared->cond_stat, &data->shared->buff_mutex);
        }
        int i = 0;
        for (i = 0; i < BUFF_SIZE; i++)
        {
            data->size_temp += data->shared->buffer_file[i];
            data->shared->buffer_file[i] = 0;
            sem_post(&data->shared->sem_elementi);
        }
        printf("[STAT] Elementi totali %d per una dimensione totale di %ld \n", i, data->size_temp);
        data->shared->full = false;
        pthread_mutex_unlock(&data->shared->buff_mutex);
        pthread_cond_signal(&data->shared->cond_stat);
        k++;
    }
    return NULL;
}

int main(int argc, char **argv)
{

    if (argc < 3)
    {
        perror("File inseriti non validi\n");
        exit(EXIT_FAILURE);
    }

    // dichiarazione degli scansionatori
    pthread_t *dir_thread = (pthread_t *)malloc(sizeof(pthread_t) * (argc - 1));
    pthread_t stat_thread;
    shared_d *shared_elements = (shared_d *)malloc(sizeof(shared_d));
    shared_elements->full = false;
    shared_elements->buffer_file = (long int *)calloc(BUFF_SIZE, sizeof(long int));
    sem_init(&shared_elements->sem_elementi, 0, BUFF_SIZE);
    dir_t *dir_data = (dir_t *)malloc(sizeof(dir_t) * (argc - 1));
    stat_t *stat_data = (stat_t *)malloc(sizeof(stat_t));
    stat_data->shared = shared_elements;
    stat_data->size_temp = 0;

    pthread_mutex_init(&shared_elements->buff_mutex, NULL);
    pthread_cond_init(&shared_elements->cond_stat, NULL);
    for (int i = 1; i < argc; i++)
    {
        strcpy(dir_data[i].pathname, argv[i]);
        dir_data[i].size = 0;
        dir_data[i].id = i;
        dir_data[i].data_s = shared_elements;
        if (pthread_create(&dir_thread[i], NULL, dir_function, &dir_data[i]) != 0)
        {
            perror("Errore nella creazione del thread\n");
            exit(EXIT_FAILURE);
        }
    }

    if (pthread_create(&stat_thread, NULL, stat_function, stat_data) != 0)
    {
        perror("Errore nella creazione del thread\n");
        exit(EXIT_FAILURE);
    }

    // Join dei thread;
    for (int i = 0; i < argc - 1; i++)
    {
        pthread_join(dir_thread[i], NULL);
    }
    pthread_join(stat_thread, NULL);

    for (int i = 0; i < BUFF_SIZE; i++)
    {
        printf(" |%ld| ", shared_elements->buffer_file[i]);
    }

    return 0;
}