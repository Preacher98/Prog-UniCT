#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
#define M 10
char fun_string(char (*str)[N][M]);
int main()
{
    char *str[N][M];
    fun_string(*str[N][M]);

}
char fun_string(char (*str)[N][M])
{
    
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; i++)
        {
            printf("\ninserisci il carattere in posizione %d  %d ",i,j);
            scanf("%s", (char *)str[j][i]);
            //while((flush=fgetc(stdin))!='\n' && flush!=EOF);
        }
    }
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; i++)
        {
            printf("\n il carattere in posizione %d  %d = %s",i,j,(char*)str[j][i]);
            
            //while((flush=fgetc(stdin))!='\n' && flush!=EOF);
        }
    }
}