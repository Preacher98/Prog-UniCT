#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct parametri
{
    int  n_lenght;
    char *string1;
    char *string2;
    char c;
};

struct parametri readInput();
char *replaceChar(struct parametri val);
char *invertString(struct parametri val);
char *sortString(struct parametri val,char *s4,char *s3);
void printString(struct parametri val,char *s5);
int main()
{
    struct parametri val=readInput();
    char *s3=replaceChar(val);
    char *s4=invertString(val);
    char *s5=sortString(val,s4,s3);
    printString(val,s5);


}

struct parametri readInput()
{
    struct parametri val={};
    val.string1=(char*)malloc(sizeof(char)*val.n_lenght);
    val.string2=(char*)malloc(sizeof(char)*val.n_lenght);

    printf("inserisci un numero minore di 256 ");
    scanf("%d",&val.n_lenght);
    if (val.n_lenght<1 || val.n_lenght>256)
    {
        fprintf(stderr,"ERRORE PARAMETRO INSERITO NON CONFORME AL PROGRAMMA!! \n");
        exit(-1);
    }
    printf("%d",val.n_lenght);

    printf("\nInserisci la prima stringa: ");
    scanf("%s",val.string1);
    val.string1[val.n_lenght+1]='\0';
    if(strlen(val.string1)<val.n_lenght || strlen(val.string1)>val.n_lenght)
    {
        fprintf(stderr,"ERRORE STRINGA NON CORRETTA\n");
        exit(-1);
    }
    printf("%s",val.string1);

    printf("\nInserisci la seconda stringa: ");
    scanf("%s",val.string2);
    val.string2[val.n_lenght+1]='\0';
    if(strlen(val.string2)<val.n_lenght || strlen(val.string2)>val.n_lenght)
    {
        fprintf(stderr,"ERRORE STRINGA NON CORRETTA\n");
        exit(-1);
    }
    printf("%s\n",val.string2);

    printf("\ninserisci un carattere: ");
    scanf("%s",&val.c);
    int y=(int) val.c;
    if(y<97 || y>122)
    {
        fprintf(stderr,"ERRORE CARATTERE NON VALIDO!!\n");
        exit(-1);
    }
    printf("%c \n",val.c);

    return val;
}
char *replaceChar(struct parametri val)
{
    char *string3=(char *)malloc(sizeof(char)*val.n_lenght+1);
    string3[val.n_lenght+1]='\0';
    strcpy(string3,val.string1);
    //printf(" %s !!",string3);
    for(int i=0;i<=val.n_lenght;i++)
    {
        if(val.string1[i]==val.c)
        {
            
            string3[i]=val.string2[i];
            //strcpy(val.string2[i],string3[i]);
            //printf("S1=%s ",&val.string1[i]);
            //printf("S3=%s ",&string3[i]);
        }
        
    }
    printf("String3=%s\n",string3);
    return string3;
}
char *invertString(struct parametri val)
{
    char *string4=(char *)malloc(sizeof(char)*val.n_lenght+1);
    string4[val.n_lenght+1]='\0';
    int i=0,j=val.n_lenght-1;
        while(j>=0)
        {
            string4[i]=val.string2[j];
            //printf("S4=%s \n",&string4[i]);
            //printf("S2=%s \n",&val.string2[j]);
           j--;
            i++;
        }
        
    
    printf("String4=%s\n",string4);
    return string4;
    
}
char *sortString(struct parametri val,char *s4,char *s3)
{
    //s4=invertString(val);
    //s3=replaceChar(val);
    char *string5=(char *)malloc(sizeof(char)*(val.n_lenght*2)+1);
    string5[(val.n_lenght*2)+1]='\0';
    string5=strcat(s4,s3);
    printf("S5=%s \n",string5);
    char min_char;
    int min_index=0;

    for (int i = 0; i <(val.n_lenght*2)-1; i++)
    {   //printf("suca");
        min_char=string5[i];
        min_index=i;
        for (int  j = i+1; j < (val.n_lenght*2); j++)
        {   //printf("suca");
            if(string5[j]<min_char)
            {   //printf("suca");
                min_char=string5[j];
                min_index=j;
            }
        }
    string5[min_index]=string5[i];   
    string5[i]=min_char; 
    }
    printf("S5ord=%s ",string5);
   
    return string5;
}
void printString(struct parametri val,char *s5)
{
    
     for (int i = 0; i <(val.n_lenght*2) ; i++)
    {
        int let=(int) s5[i];
        if(let%2!=0)
        {s5[i]='*';}
    }
    printf("S5*=%s",s5);
}

/*int i=0, indiceMinimo=0, j=0;
    for(i=0; i<Array_Length-1; i++){
        minimo = Array[i];
        indiceMinimo = i;
        for(j=i+1; j<Array_Length; j++){
            if(Array[j] < minimo){
                minimo = Array[j];
                indiceMinimo = j;
            }
        }        
        Array[indiceMinimo]=Array[i];
        Array[i]=minimo;        
    }*/