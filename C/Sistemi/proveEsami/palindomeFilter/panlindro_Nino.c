#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdbool.h>
//#include "../lib-misc.h"
#include <pthread.h>

#define BUFFSIZE 1000

typedef struct{

    char buffer [BUFFSIZE];
    char filename[20];
    pthread_mutex_t mutex_b;
    pthread_cond_t s_p, s_r, s_w;
    bool done;

} shared_data;

typedef struct{

    int id;
    shared_data share;

} t_data;


void *F_TR(void *args){
    shared_data *shared = (shared_data*) args;
    FILE *file_txt = fopen(shared->filename, "r");
    
    char buff[BUFFSIZE];
    while(1){
            pthread_mutex_lock(&shared->mutex_b);
            printf("ti odio maledetto linguaggio C di merda \n");
            pthread_cond_wait(&shared->s_r, &shared->mutex_b);
            
            if(fgets(buff, BUFFSIZE, file_txt) == NULL){
                printf("\n[R] Ho terminato la lettura del file mi avvio a chiudere il programma.\n");
                shared->done = true;
                pthread_cond_signal(&shared->s_p);
                pthread_mutex_unlock(&shared->mutex_b);
                break;
                
            }
            buff[strcspn(buff, "\n")] = '\0';
            strcpy(shared->buffer, buff);
            printf("\n[R] La parola è: %s\n", shared->buffer);
            printf("[R] Aspetto che si svegli P.\n\n");
            pthread_cond_signal(&shared->s_p);
            pthread_mutex_unlock(&shared->mutex_b);


        }
        fclose(file_txt);
       
        return NULL;
    }

    




void *F_TP(void *args){

    shared_data *shared = (shared_data *)args;
    
    while (true)
    {
    pthread_mutex_lock(&shared->mutex_b);
    pthread_cond_wait(&shared->s_p,&shared->mutex_b);

     if(shared->done){
        printf("[P] Concludo l'esecuzione.\n");
                                                            //chat
        pthread_cond_signal(&shared->s_w);
        pthread_mutex_unlock(&shared->mutex_b);
        break;
    }
    
    bool pal = true;
    int coda = strlen(shared->buffer) - 1;
    printf("[P] Controllo se la parola è palindroma.\n");
    for (int i = 0; i < strlen(shared->buffer) / 2; i++) {
        if (shared->buffer[i] != shared->buffer[coda - i]) {
            printf("[P] La parola non è palindroma.\n\n");
            printf("[P] Risveglio R.\n");
            
            pthread_cond_signal(&shared->s_r);
            //pthread_mutex_unlock(&shared->mutex_b);
            pal = false;
            break;
        }
    }


    if (pal) {
        printf("[P] Aspetto che si svegli W.\n");
        
        pthread_cond_signal(&shared->s_w);
        //pthread_mutex_unlock(&shared->mutex_b);
    }
    pthread_mutex_unlock(&shared->mutex_b);
    
    /*if(shared->done){
        printf("[P] Concludo l'esecuzione.\n");
        
        pthread_cond_signal(&shared->s_w);
        pthread_mutex_unlock(&shared->mutex_b);
        break;
    }*/
    }
    return NULL;
}



void *F_TW(void *args){
    shared_data *shared = (shared_data*) args;
        
    while (true)
    {
        pthread_mutex_lock(&shared->mutex_b);
    pthread_cond_wait(&shared->s_w, &shared->mutex_b);
    
    if(shared->done){
        printf("[W] Concludo l'esecuzione.\n");
        pthread_mutex_unlock(&shared->mutex_b);
        return NULL;
    }
    printf("\n[W] La parola '%s' è palindroma.\n", shared->buffer);
    
    pthread_cond_signal(&shared->s_r);
    pthread_mutex_unlock(&shared->mutex_b);
    }
    return NULL;
}






int main(int argc,char *argv[]){
    if(argc != 2){
        perror("Errore nell'inserimento dell'input\n");
        exit(EXIT_FAILURE);
    }
    shared_data *share = (shared_data*) malloc(sizeof(shared_data));
    share->done = false;
    strcpy(share->filename, argv[1]);

    if(pthread_mutex_init(&share->mutex_b, NULL) != 0){
        
        perror("Errore nella creazione del mutex.\n");
        exit(EXIT_FAILURE);
        
    }

    if(pthread_cond_init(&share->s_p, NULL) != 0){

        perror("Errore nella creazione del semaforo P.\n");
        exit(EXIT_FAILURE);
    }


     if(pthread_cond_init(&share->s_r, NULL) != 0){

        perror("Errore nella creazione del semaforo R.\n");
        exit(EXIT_FAILURE);

    }


     if(pthread_cond_init(&share->s_w, NULL) != 0){

        perror("Errore nella creazione del semaforo P.\n");
        exit(EXIT_FAILURE);

    }


    pthread_t W, P, R;
    pthread_create (&R, NULL, F_TR, share );
    pthread_create (&P, NULL, F_TP, share );
    pthread_create (&W, NULL, F_TW, share );

    pthread_mutex_lock(&share->mutex_b);
    pthread_cond_signal(&share->s_r);  
    pthread_mutex_unlock(&share->mutex_b);

    
    pthread_join(R,NULL);
    pthread_cond_destroy(&share->s_r);
    pthread_join(P,NULL);
    pthread_cond_destroy(&share->s_p);
    pthread_join(W, NULL);
    pthread_cond_destroy(&share->s_w);
    pthread_mutex_destroy(&share->mutex_b);
    free(share);

    printf("PROGRAMMA COMPLETATO.\n");
    exit(EXIT_SUCCESS);
}