#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<fcntl.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<sys/mman.h>
//Riconducibile al problema lettori-scrittori, perché i thread possono essere sia lettori che scrittori
//Utilizzo di define per semplificare la situazione
//mutex per bloccare in modo univoco la scrittura  e la lettura, quindi due mutex read_m e write_m, bloccare la lettura durante la scrittura per evitare incosistenza dei dati
//aggiungere un sem_t per ogni thread per farlo creare un array di semafori con al stessa dimensione del numero di thread.

//Passi: 1 fare la struttura, 2 fare i thread, 3 Verificare che funziona tutto 4 inserire gli elementi di sincronizzazione 5 Deallocare tutto


typedef enum{ADD, SUB, MUL}operationi;

//struct che condividono tutti i thread
typedef struct shared_calc_thread
{
  long long operando_1;
  long long operando_2;
  long long risultato;
  int op_code;
  int richiedente; 
  int exit;
}share_t;

typedef struct thread_calculator
{
    char *filename;
    int id;
   
}calc_thread;


int main(int argc, char **argv){

    int n_file_calc = argc - 1;
    if (n_file_calc == 0)
    {
        perror("Errore nell'inserimento dei parametri\n");
        exit(EXIT_FAILURE);
    }
    
    share_t *shared_s = (share_t*)malloc(sizeof(share_t));

}