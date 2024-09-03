#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
#define M 10
int palindromo(char **matrice[]);
int main()
{
    char ***matrice=(char ***)malloc(sizeof(char**)*N);
    for(int i=0;i<M;i++)
    {matrice[i]=(char **)malloc(sizeof(char*)*M);}

    for(int i=0;i<M;i++)
    {
        for(int j=0; j<N; j++)
        {   int lungh=rand()%(10-5+1)+10;
            matrice[j][i]=(char *)malloc(sizeof(char *)*M);
            int x=0;
            for( x=0; x<lungh; x++)
            {
                matrice[j][i][x]=rand()%('b'-'a'+1)+'a'; //generazione di stringhe pseudo-casuali
                
            }
            matrice[j][i][x]='\0';

            printf(" %s ",matrice[j][i]);
        }
        printf("\n");
    }
palindromo(matrice);
}

int palindromo(char **matrice[])
{

    for(int i=0;i<M; i++)
    {
        for(int j=0; j<N; j++)
        {
            
                int p_count=0;  
                char temp[15];
               strcpy(temp,matrice[j][i]);
                int len=strlen(temp);
                for(int x=0; x<len/2;x++)
                {
                    
                  if(matrice[j][i][x] == temp[len-x-1])
                  {
                    //printf("%c  ",temp[x]);
                     p_count++; 
                    if(p_count==(len/2))
                    {printf("%s palindroma\n",matrice[j][i]);p_count=0;}
                  }
                }
            
            
            //printf("%s \n",matrice[j][i]);
       }
        printf("\n"); 
    }
}