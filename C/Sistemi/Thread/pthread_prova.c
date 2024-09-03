#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

/*INDICAZIONI DI BASE
Dato un programma è opportuno identificare cosa i thread condividono e cosa invece no, di conseguenza è necessario creare delle strutture dati
che permettono di essere passate tra i thread. Chiaramente distinguere quelle condivise da quelle personali*/



int i=0;

void* funzione_thread(void* arg){
    int value= *(int*)arg;
    
    for (; i < 100; i++)
    {
       printf("n: %d sono il thread %lu, il numero è %d\n",i,(unsigned long)pthread_self(), value);
    }
    
    return NULL;
}

void* funzione_thread2(void* arg){
    int value= *(int*)arg;
    
    for (; i < 100; i++)
    {
       printf("n: %d sono il thread %lu, il numero è %d\n",i ,(unsigned long)pthread_self(), value);
    }
    
    return NULL;
}

int main(){
    /*Il tipo pthread_t permette di creare delle variabili che pososno contenere il TID[Thread ID] di ogni thread*/
    pthread_t thread_id, thread_id2;
    
    int arg=70;
    /*La funzione pthread_create permette di creare un thread, tuttavia è necessario specificare dei parametri per poterlo creare al meglio
    1 = Puntatore al TID,
    2 = Attributi che possono dare caratteristiche al thread, NULL di base
    3 = La funzione thread che deve eseguire
    4 = I parametri da passare alla funzione thread.
    In questo caso arg è un valore qualsiasi e poteva essere anche una stringa*/
    if(pthread_create(&thread_id, NULL, funzione_thread, &arg) != 0){
        perror("Errore nella creazione");
        return 1;}
    
    
    int arg2=71;
    if(pthread_create(&thread_id2, NULL, funzione_thread2, &arg2) != 0){
        perror("Errore nella creazione");
        return 1;}
    /*pthread_join permette di attendere la terminazione di un thread, questo è la forma di sincronismo più base e agisce nel cambio di contesto*/
    pthread_join(thread_id, NULL);
    pthread_join(thread_id2, NULL);
    
}


