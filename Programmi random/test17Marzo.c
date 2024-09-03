#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

unsigned get_random(){
     static unsigned int m_w=123456;
     static unsigned int m_z=789123;
     m_z=36969*(m_z & 65535)+(m_z>>16);
     m_w=18000*(m_w & 65535)+(m_w>>16);
     return (m_z<<16)+m_w;
}

 typedef struct element{
    int a;
    int b;
    double alpha;
    double beta;
}element;

struct element readInput(int argc,char*argv[]){
element arg;
    if (argc != 5) {
        fprintf(stderr,"Errore: inserisci i valori di a, b, alpha e beta.\n");
        fprintf (stderr,"uso corretto 'int' 'int' 'double' 'double'.\n");
        exit(1);
    }
    char **end=malloc(sizeof(char*));
    arg.a=(int)strtol(argv[1],end,0);
    if (!end){
        fprintf(stderr,"Errore, il primo parametro deve essere di tipo intero.\n");
        exit(-1);
    }
    if(arg.a<5||arg.a>20){
        fprintf(stderr,"Errore il primo parametro dev'essere compreso nel range '5-20'.\n");
        exit(-1);
    }

    arg.b =(int)strtol(argv[2],end,0);
    if(!end){
        fprintf(stderr,"Errore il secondo parametro dev'essere compreso nel range '5-20'.\n");
        exit(-1);
    }
    if(arg.b<5||arg.b>20){
        fprintf(stderr,"Errore,il secondo parametro dev'essere compreso nel range '5-20'.\n");
        exit(-1);
    }
    
    arg.alpha =(double)strtol(argv[3],end,0);
    if(!end){
        fprintf(stderr,"errore,il terzo parametro dev'essere di tipo double.\n");
        exit(-1);
    }
    if(arg.alpha<10||arg.alpha>20){
        fprintf(stderr,"errore il terzo parametro dev'essere compreso nel range '10-20'.\n");
        exit(-1);
    }
    arg.beta = (double)strtol(argv[4],end,0);
    if(!end){
        fprintf(stderr,"Errore,il quarto parametro dev'essere di tipo double.\n");
        exit(-1);
    }
    if(arg.beta<1||arg.beta>5){
        fprintf(stderr,"Errore,il quarto paramentro dev'esssere compreso nel range 1-5.\n");
        exit(-1);
    }


    return arg;
}
    



double ***allocmatrix(int a,int b){
double ***matrix=(double***)calloc(a,sizeof(double**));
for(unsigned short i =0; i<a; i++){
   matrix[i]=(double**)calloc(b,sizeof(double*));        
}
return matrix;
}
double *genrand();

double *genrand()
{
    double *ptr=(double *)malloc(sizeof(double));
    *ptr=get_random()/((double)UINT_MAX)*((12.3-4.6+1)+4.6);
    return ptr;
}
void genmatrix(double ***matrix, int a, int b, double alpha, double beta) {
    double x = alpha - beta;
    double y = alpha + beta;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) 
        {
            matrix[i][j]=genrand();
        }
    }
}






    



void printmatrix(double***matrix,int a ,int b){
    for(int i=0; i<a; i++){
        for(int j=0; j<b; j++){
             printf("%.2lf ",*matrix[i][j]);
                }
        printf("\n");
            }
        }
        



int main(int argc,char *argv[]){
struct element m=readInput(argc,argv);
//printf("hola\n");
double***matrix=allocmatrix(m.a,m.b);
//printf("hola\n");
genmatrix(matrix,m.a,m.b,m.alpha,m.beta);
//printf("hola\n");
printmatrix(matrix,m.a,m.b);
//printf("hola\n");



}

