#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
struct filetesto
{
    char string[100];
    int counter;
    struct filetesto *next;
};


int readIO(int argc,char *argv[]);
struct filetesto *printfile(struct filetesto *head);
struct filetesto *Headcreation();

int main(int argc,char *argv[],struct filetesto *head)
{
    readIO(argc,argv);
    
    printfile(head);
}
struct filetesto *Headcreation()
{
    struct filetesto *head=(struct filetesto *)malloc(sizeof(struct filetesto));
    head=NULL;
    return head;
}
int readIO(int argc,char *argv[])
{
    //printf("ciao");
    int N=0;
    N=atoi(argv[1]);
    if(N<0 || N>100)
    {fprintf(stderr,"INPUT ERRORE INVALID INTEGER NUMBER ! \n"); exit(-1);}
    //printf("ciao ");
    return N;
}
struct filetesto *printfile(struct filetesto *head)
{
    const char *nameF="testo.txt";
    char *mode="r+";
    bool flag=false;
    char string[1000];
    head=Headcreation();
    FILE *Fp = fopen(nameF,mode);
     if (!Fp)
    {
        fprintf(stderr, "\n Error opening file  with mode ");
        perror("");
    }

    while(!flag)
    {
        char *line = fgets(string,1000, Fp);
        if(line != NULL)
        {
            char *lineTok= strtok(string," \n");
            char *FirstTok = lineTok;
            int count = 0;
            do
            {
                if (strcmp(FirstTok,lineTok)==0)
                {
                    count++;
                }
                
            } while ((lineTok=strtok(NULL," \n")));
            struct filetesto *new_node=(struct filetesto *)malloc(sizeof(struct filetesto));
            new_node->counter=count;
            strcpy(new_node->string,FirstTok);
            new_node->next=head;
            head=new_node;
        }else{flag=true;}
    }
    

   
    fclose(Fp);
    while (head !=NULL)
    {
        printf("%s totali occorrenze nella riga %d \n",head->string,head->counter);
        head=head->next;
    }
    
    return head;

}