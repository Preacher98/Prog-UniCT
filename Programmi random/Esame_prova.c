#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct argomenti{
    int k;
    int N;
    int M;
    char w;
};

unsigned int get_random() {
static unsigned int m_w = 123456;
static unsigned int m_z = 789123;
m_z = 36969 * (m_z & 65535) + (m_z >> 16);
m_w = 18000 * (m_w & 65535) + (m_w >> 16);
return (m_z << 16) + m_w;
}
struct argomenti readInput(int argc,char *argv[]);
char ***allocateS(struct argomenti arg);
char *genString(struct argomenti arg);
char ***fillS(char ***S,struct argomenti arg);
void printMatrix(char ***S,struct argomenti arg);
char ***sortS(char ***S,struct argomenti arg);
void printMatrix2(char ***S,struct argomenti arg);
void printMax(char ***S,struct argomenti arg);

    
int main(int argc,char *argv[])
{  

struct argomenti arg=readInput(argc,argv);
char ***S=allocateS(arg);
fillS(S,arg);
printMatrix(S,arg);
sortS(S,arg);
printMatrix2(S,arg);
printMax(S,arg);


}

struct argomenti readInput(int argc,char *argv[])
{
    struct argomenti arg;
        //printf("Inserisci il numero k in un range di 10-15= ");
        //scanf("%d",&argo.k);
        arg.k=atoi(argv[1]);
        //printf("%d",argo.k);
        if(arg.k<10 || arg.k>15)
        {
            fprintf(stderr,"Errore valore inserito non valido, esecuzione terminata!!!!!\n");
            exit(-1);
        }


        //printf("\ninsersici il numero N in un range 4-8= ");
        //scanf("%d",&argo.N);
        arg.N=atoi(argv[2]);
        if(arg.N<4 || arg.N>8)
        {
            fprintf(stderr,"\nErrore valore inserito non valido, esecuzione terminata!!!!!\n"); 
            exit(-1);
        }
        
        //printf("\ninserisci il numero M in un range 4-8= ");
        //scanf("%d",&argo.M);
        arg.M=atoi(argv[3]);
        if(arg.M<4 || arg.M>8)
        {
            fprintf(stderr,"\nErrore valore inserito non valido, esecuzione terminata!!!!! %d\n",arg.M);
            exit(-1);
        }
        //printf("\nInserisci il carattere da inserire in w in un range [a-z]= ");
        arg.w=argv[4][0];
        int y=(int) arg.w;
        //printf("%d",y);
        if(y<97 || y>122)
        {
            fprintf(stderr,"\nErrore valore inserito non valido, esecuzione terminata!!!!!\n");
            exit(-1);
        }
    return arg;
}
char ***allocateS(struct argomenti arg)
{
    char ***S=(char ***)malloc(sizeof(char **)*arg.N);
    for (int i = 0; i < arg.N; i++)
    {
        S[i]=(char **)malloc(sizeof(char *)*arg.M);
    }
    return S;
}
char *genString(struct argomenti arg)
{
    //struct argomenti arg;
    char *string=(char *)malloc(sizeof(char)*(arg.k+1));
    int i=0;
    for ( i = 0; i < arg.k; i++)
    {
        string[i]=get_random()%('z'-'a'+1)+'a';
    }
    
    string[i+1]='\0';
    return string;


}
char ***fillS(char ***S,struct argomenti arg)
{
    //S=allocateS(arg);
    //printf("ciao %d %d \n",arg.N,arg.M);
    for (int i = 0; i < arg.N; i++)
    { //printf("ciao\n");
        for (int j = 0; j < arg.M; j++)
        {
            //printf("ciao\n");
            S[i][j]=genString(arg);
            //printf("%s ",S[i][j]);
        }
        //printf("\n");
    }
    return S;
}
void printMatrix(char ***S,struct argomenti arg)
{
    //S=fillS(S,arg);
    for (int i = 0; i < arg.N; i++)
    {
        for (int j = 0; j < arg.M; j++)
        {
            printf("%s ",S[i][j]);
        }
        printf("\n");
    }  


    
}
void printMatrix2(char ***S,struct argomenti arg)
{
    printf("\n");
    for (int i = 0; i < arg.N; i++)
    {
        for (int j = 0; j < arg.M; j++)
        {
            printf("%s ",S[i][j]);
        }
        printf("\n");
    }  

}

char ***sortS(char ***S,struct argomenti arg)
{
    for(int j = 0; j < arg.M; j++)
    { 
        for (int passi = 0; passi < arg.N-1; passi++)
        {
            for (int i = 0; i < arg.N-1-passi; i++)
            {
                if(strcmp(S[i][j],S[i+1][j])>0)
                {
                    char *temp=S[i][j];
                    S[i][j]=S[i+1][j];
                    S[i+1][j]=temp;
                    //printf("%s  ",S[i][j]);
                    //printf("%d %d %d ",j,passi,i);
                    
                    
                }
            }  
        }  
    }
 
    return S;
}
void printMax(char ***S,struct argomenti arg)
{
    int counter=0;
    int count_max=0;
    printf("\n");
    for (int i = 0; i < arg.N; i++)
    {
        for (int j = 0; j < arg.M; j++)
        {
            for (int y = 0; y < arg.k; y++)
            {
                if(S[i][j][y]==arg.w)
                {
                    S[i][j][y]='*';
                    
                    counter++;
                }
                
                
                
            }
            if (counter >count_max)
                {
                    count_max=counter;
                }
            counter=0;
        }
    }
    printf("Le occorrenze trovate trovate con la lettera %c sono: %d\n",arg.w,count_max);
    printf("\n");
    /*for (int i = 0; i < arg.N; i++)
    {
        for (int j = 0; j < arg.M; j++)
        {
            printf("%s ",S[i][j]);
        }
        printf("\n");
    }  
    */
   printMatrix(S,arg);
}
