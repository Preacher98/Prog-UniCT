#include<stdio.h>
#include<stdlib.h>

#define PARENT(i) ((I-1)/2)
#define LEFT(i) (1+i*2)
#define RIGHT(i) (i*2+2)

typedef struct 
{
    int *Array;    //Array delle key
    int lunghezza; //Lunghezza massima dell'heap
    int heap_size; //lunghezza attuale dell'heap
}Heap;

Heap* create_Heap(int lunghezza); 
void insert_Heap(Heap* h, int k);
void swap(int *x, int *y);
int main(int argc, char const *argv[]){
    Heap* new_heap = (Heap*) malloc(sizeof(Heap)); 
    new_heap = create_Heap(10);
    insert_Heap(new_heap,3);
    return 0;
}

//Creiamo un heap con questa funzione che ritorna appunto un heap vuoto ma allocato
Heap* create_Heap(int len){
    Heap* h = (Heap*) malloc(sizeof(Heap));
    h->lunghezza = len;
    h->heap_size = 0;
    h->Array = (int*)sizeof(len * sizeof(int));
    return h;
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void insert_Heap(Heap* h, int k){
    
    if(h->heap_size == h->lunghezza) {printf("Heap Pieno.\n"); return;} //controlliamo se l'heap è pieno

    h->heap_size++;




}