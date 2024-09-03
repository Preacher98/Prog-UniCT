#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

typedef struct Array_randomico
{
    int Arr[1000];
    int dim;
}Array1;

int somma = 0;

pthread_mutex_t sum_mutex;
void randomize_Array(Array1 *arr){
    
    srand(time(0));
    
    for (int i = 0; i < arr->dim; i++)
    {
        arr->Arr[i]=(rand()%30)+1;
        //printf("%d\t",arr->Arr[i]);
    } 
    
}

void* function_thread1(void* arr){
    Array1* array = (Array1*) arr;
    for (int i = 0; i < array->dim/2; i++)
    {
        pthread_mutex_lock(&sum_mutex);
        somma = somma + array->Arr[i];
        printf("t1 %d + %d\n",somma, array->Arr[i]);
        pthread_mutex_unlock(&sum_mutex);
    }
    printf("io thread1 ho sommato= %d\n",somma);
    return NULL;
}

void* function_thread2(void* arr){
    Array1* array = (Array1*) arr;
    for (int i = array->dim/2; i < array->dim; i++)
    {   
        pthread_mutex_lock(&sum_mutex);
        somma = somma + array->Arr[i];
        printf("t2 %d + %d\n",somma, array->Arr[i]);
        pthread_mutex_unlock(&sum_mutex);
    }
    printf("io thread2 ho sommato= %d\n",somma);
    return NULL;
}
int main(){

    Array1 arr;
    arr.dim=1000;
    randomize_Array(&arr);
    pthread_mutex_init(&sum_mutex, NULL);
    /*for (int i = 0; i < arr.dim; i++)
    {
       printf("[%d] = %d\n",i , arr.Arr[i]);
    }*/

   pthread_t thread1,thread2;

    if (pthread_create(&thread1, NULL, function_thread1, &arr) != 0)
    {
        perror("errore nella creazione del thread! \n");
        return 1;
    }
    
    if (pthread_create(&thread2, NULL, function_thread2, &arr) != 0)
    {
        perror("errore nella creazione del thread! \n");
        return 1;
    }

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    printf("somma = %d\n",somma);
    pthread_mutex_destroy(&sum_mutex);
}