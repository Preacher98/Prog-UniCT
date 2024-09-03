#include <stdio.h>
#include <stdlib.h>
#define N 5
int vettore[N]={1,2,3,4,5};
int somma_vettore(int sum);
int main()
{
    /*int vettore[N],i=0;
    while(i<N)
    {
        printf("\ninserisci il numero ");
        scanf("%d",&vettore[i]);
        i++;
    }
    i=0;
    int sum=somma_vettore(vettore);
    printf("somma totale %d",sum);*/
}
int somma_vettore(int sum)
{
    int i=0;
    sum=vettore[i]+vettore[i+1];
    i++;
    printf("sum=%d",sum);
    return somma_vettore(sum);
}