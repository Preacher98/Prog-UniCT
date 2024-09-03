#include <stdio.h>
#include <stdlib.h>

unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}
void readInput(int N, double x,double y,int argc,char *argv[]);
double **GentMatrix(int N,double x, double y);
double GenRandom(double x,double y);
void DiagonalMatrix(double **A,int N);
void ArrayMatrix(double **A,int counter,int N,double minP,double maxP);
int main(int argc,char *argv[])
{
    int N;
    double x,y;
    readInput(N,x,y,argc,argv);
}

void readInput(int N, double x,double y,int argc,char *argv[])
{
    N=atoi(argv[1]);
    if (N<10 || N>20)
    {
        fprintf(stderr,"ERRORE ");
        exit(-1);
    }
    x=atof(argv[2]);
    y=atof(argv[3]);
    if (y>30.0 || y<x )
    {
        fprintf(stderr,"ERRORE");
        exit(-1);
    }
    if(x>y || x<5.0)
    {
        fprintf(stderr,"ERRORE");
        exit(-1);
    }
    printf("N=%d  x=%.3lf y=%.3lf \n",N,x,y);
   GentMatrix(N,x,y);
   //double prova= GenRandom(x,y);
   //printf(" %lf \n",prova);
}
double **GentMatrix(int N,double x, double y)
{
    double **A=(double **)malloc(sizeof(double*)*N);
    for (int i = 0; i < N; i++)
    {
        A[i]=(double *)malloc(sizeof(double)*N);
    }
    //Caricamento della matrice
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j]=GenRandom(x,y);
        }
        
    }
    //stampa di controllo
        for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
           printf("[%.2lf]",A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    DiagonalMatrix(A,N);
    
    return A;
    
}
void ArrayMatrix(double **A,int counter,int N,double minP,double maxP)
{
    double *Array=(double *)malloc(sizeof(double)*counter);
    int k=0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (A[i][j]>minP && A[i][j]<maxP)
            {
                Array[k]=A[i][j];
                k++;
            }
        }
    }
    for (int i = 0; i < counter-1; i++)
    {
        int min=i;
        for (int j = i+1; j < counter; j++)
        {
            if (Array[j]<Array[min])
            {
                min=j;
            }
            
        }
        double temp=Array[min];
        Array[min]=Array[i];
        Array[i]=temp;
    }
    double media=0;
    for (int i = 0; i < counter; i++)
    {
        media+=Array[i];
        if ((i%5)==0)
        {
            printf("\n");
        }
        printf("[%.2lf] ",Array[i]);
    }
    media=media/counter;
    printf("\n La media è %.4lf",media);
    
}
void DiagonalMatrix(double **A,int N)
{
    int j=N-1,i=0;;
    double minP=A[0][0],maxP=A[i][j];
    for (i = 0; i < N; i++)
    {
        if (minP>A[i][i])
        {
             minP=A[i][i];
        }  
    }
    printf("MinP=%.2lf ",minP);
    
    for (i = 0; i < N; i++)
    {
        if (maxP<A[i][j])
        {
            maxP=A[i][j];
        }
        j--;
    }
    printf("Maxp=%.2lf ",maxP);
    int counter=0;
    for (int s = 0; s < N; s++)
    {
    for (int k = 0; k < N; k++)
    {
        if (A[s][k]>minP && A[s][k]<maxP)
        {
            counter++;
        } 
    }
    }
    printf("(%d) elementi compresi tra minP e maxP.\n ",counter);
    ArrayMatrix(A,counter,N,minP,maxP);
    
}
double GenRandom(double x,double y)
{
    double random=((double)get_random()/RAND_MAX)*(y-x)+x;
    return random;
}