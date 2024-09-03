#include<stdio.h>
#include<stdlib.h>
#include<time.h>


unsigned int funct_matrice(unsigned int **A,unsigned int **B,int n,int m, int k); // prototipo funzione

int main()
{
     int n=0,m=0,k=0;

    printf("inserisci le dimensioni \n"); //Inserimento di n,m,k da parte dell'utente
    printf("n=");
    scanf("%d",&n);
    printf("\nm=");
    scanf("%d",&m);
    printf("\nk=");
    scanf("%d",&k); //Fine inserimento delle dimensioni

    srand(time(0)); //Dichiarazione seme rand
    unsigned int **A=(unsigned int **)malloc(sizeof(unsigned int *)*n);
    unsigned int **B=(unsigned int **)malloc(sizeof(unsigned int *)*k);
    for (int i = 0; i < n; i++)// Allocamento di A
    {
        A[i]=(unsigned int *)malloc(sizeof(unsigned int)*m);
    }
    for (int i = 0; i < k; i++)// Allocamento di B 
    {
        B[i]=(unsigned int *)malloc(sizeof(unsigned int)*n);
    }

     for(int i=0;i<n;i++)   //For di caricamento di A con numeri pseudocasuali
    {
        for(int j=0;j<m;j++)
        {
            *(*(A+i)+j)=rand()%(5-1+1)+5;
            printf("%d ",*(*(A+i)+j));
        }
        printf("\n");
    }
    printf("\n");
     for(int i=0;i<k;i++) //For di caricamento di B con numeri Pseudocasuali 
    {
        for(int j=0;j<n;j++)
        {
            *(*(B+i)+j)=rand()%(5-1+1)+5;
            printf("%d ",*(*(B+i)+j));
        }
        printf("\n");
    }
funct_matrice(A,B,n,m,k); // Chiamata alla funzione 

free(A);
free(B); //Deallocazione delle matrici A e B
}

unsigned int funct_matrice(unsigned int **A,unsigned int **B,int n, int m, int k) //Funzione con passaggio delle matrici
{
    
    double *C = (double *)malloc(sizeof(double)*n); //Allocamento dinamico di un array double C di dimensioni n
    double rig_sum=0,col_mul=1; //variabili somma di righe e prodotto di colonne
    for(int o=0;o<n;o++) //Ciclo For per l'array C
    {
        
    for(int i=0;i<n;i++) //Ciclo for per le matrici
    {
        rig_sum=0,col_mul=1;
        for(int f=0;f<m;f++) //For per le righe di A
        {
            rig_sum+=A[i][f];
           // printf("rigsum=%.4lf\n",rig_sum);
        }

    
        for(int j=0;j<k;j++) //For per le colonne di B
        {
           col_mul*=B[j][i];
            //printf("colmul=%.4lf\n",col_mul);
        }
        
         C[o]=(double)col_mul/rig_sum; //Assegnamento alla posizione o dell'array di C
         if(o==i)printf("C[%d]=%.4lf ",o,C[o]); //Stampa 
        
    }
       
    printf("\n");
    }
free(C); //Liberare la memoria
}