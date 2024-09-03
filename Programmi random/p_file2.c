#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//prototipi
void gestione_matrice();
double generazione_rand();
void stampa_matrice(double **matrice, short int n, short int m);
void File_matrice(double **matrice, short int n, short int m);
void Carica_matrice(short int n, short int m, const char *nomefile, FILE *Fmanager, char *modalita);
void trasposta_matrice(double **matrice, short int n, short int m,const char *nomefile, FILE *Fmanager, char *modalita);
int main()
{
    srand(time(0));
    gestione_matrice();
}
void Carica_matrice(short int n, short int m, const char *nomefile, FILE *Fmanager, char *modalita)
{
    modalita="r";
    char s[6];
    Fmanager=fopen(nomefile,modalita);

    double **mat= (double **)malloc(sizeof(double *)*m);
    for (int i = 0; i < m; i++)
    {
       mat[i]=(double *) malloc(sizeof(double)*n);
    }
    
    //fopen(nomefile,modalita);
    printf("\n");
    /*long int tell=ftell(Fmanager);
    printf("\n%ld\n",tell);*/
    fseek(Fmanager,23,SEEK_CUR);
    do{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
           //fgets(s,5,Fmanager);
           fscanf(Fmanager,"%lf",&mat[i][j]);
           /*double temp=atof(s);
           mat[i][j]=temp;*/
           //printf("[%s] ",s);
           printf("%.2lf ",mat[i][j]);
        }
        printf("\n");
    }}while(feof(Fmanager));

    trasposta_matrice(mat,n,m,nomefile,Fmanager,modalita);
    
    fclose(Fmanager);    

}
void File_matrice(double **matrice, short int n, short int m)
{
    const char *nomefile = "rw.txt";
    char *modalita = "w+"; // Sono puntatori perche la maggior parte delle funzioni necessitano di puntatori
    FILE *Fmanager = fopen(nomefile, modalita);
    if (!Fmanager)
    {
        fprintf(stderr, "\n Error opening file %s with mode %s", nomefile, modalita);
        perror("");
    }
    fprintf(Fmanager,"Matrice dimensioni: %hdx%hd\n",n,m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fprintf(Fmanager, "%.2lf ", matrice[i][j]);
        }
        fprintf(Fmanager,"\n");
    }

    fclose(Fmanager);
    Carica_matrice(n,m,nomefile,Fmanager,modalita);
}
void stampa_matrice(double **matrice, short int n, short int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("[%.2lf]", matrice[i][j]);
        }
        printf("\n");
    }
    File_matrice(matrice,n,m);
}
void trasposta_matrice(double **mat, short int n, short int m,const char *nomefile, FILE *Fmanager, char *modalita)
{
    modalita="a";
    Fmanager=fopen(nomefile,modalita);
        printf("\n");
        fprintf(Fmanager,"Matrice trasposta\n");

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%.2lf " ,mat[j][i]);
            fprintf(Fmanager,"%.2lf ",mat[j][i]);
        }
        fprintf(Fmanager,"\n");
        printf("\n");
    }
    fclose(Fmanager);
}
void gestione_matrice()
{
    short int n = 5, m = 6;
    double **matrice = (double **)malloc(sizeof(double *) * n);
    for (int i = 0; i < n; i++)
    {
        matrice[i] = (double *)malloc(sizeof(double) * m);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrice[i][j] = generazione_rand();
        }
    }
    stampa_matrice(matrice, n, m);
}
double generazione_rand()
{
    double numero = 0;
    numero = rand() / (RAND_MAX * 1.0) * (9);
    return numero;
}

