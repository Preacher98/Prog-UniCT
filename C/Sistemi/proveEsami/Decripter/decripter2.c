#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<semaphore.h>

#define BUFFER_SIZE 100
#define ALPHABET_SIZE 26
#define MAX_KEY 100

//Struttura dati condivisa tra thread
typedef struct shared_argument_thread
{
    char S_buffer[BUFFER_SIZE];
    sem_t *sem_main;

}S_Arg_Thread;

typedef struct private_argument_thread
{
    char key_buff[ALPHABET_SIZE];
    S_Arg_Thread *thread_arg;
};


int main(int argc, char ** argv){
    //Controllo inserimento dati
    if (argc < 3 || argc > 4)
    {
        perror("Errore nell'inserimento dei dati\n");
        exit(EXIT_FAILURE);
    }
    /*In posizione di argv[1] e argv[2] e argv[3] ci sono i nomi dei file*/
    //Main thread
    
    char keys[MAX_KEY][26];
    
    

}

