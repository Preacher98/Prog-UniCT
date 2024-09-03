#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int get_random() {
static unsigned int m_w = 123456;
static unsigned int m_z = 789123;
m_z = 36969 * (m_z & 65535) + (m_z >> 16);
m_w = 18000 * (m_w & 65535) + (m_w >> 16);
return (m_z << 16) + m_w;
}

struct parametri 
{
    int N;
    char w;
};
struct nodo 
{
    char *string;
    struct nodo* next;
};
//Prototipi
struct parametri readInput(int argc,char *argv[],struct parametri P);
struct nodo *genlist(struct nodo *head,struct parametri P);
char *genString();
void printlist(struct nodo *head);
int cont(struct nodo *head,struct parametri P);
struct nodo *sortList(struct nodo *head);

int main(int argc,char *argv[])
{
    
    struct parametri P=readInput(argc,argv,P);
    struct nodo *head=(struct nodo *)malloc(sizeof(struct nodo)); 
    head=genlist(head,P);
    printlist(head);
    printf("\n");
    head=sortList(head);
    printlist(head);
    int c=cont(head,P);
    printf("Trovate %d occorrenze della lettera '%c'. \n",c,P.w);

}

struct parametri readInput(int argc,char *argv[],struct parametri P)
{
    //struct nodo *p=(struct nodo*)malloc(sizeof(struct nodo));
    P.N=atoi(argv[1]);
    if (P.N<10 || P.N>20)
    {
      fprintf(stderr,"Invalid input, please restart the operation !! \n");
      exit(-1);
    }
    P.w=(char)argv[2][0];
    if (P.w<'a' || P.w>'z')
    {
      fprintf(stderr,"Invalid input, please restart the operation !! \n");
      exit(-1);  
    }
    printf("questi sono gli  che hai inserito: %d,  %c  \n",P.N,P.w);
    return P;
    

}
char *genString()
{
    int L=get_random()%(15-5+1)+5;
    char *string=(char*)malloc(sizeof(char)*L);
    for (int i = 0; i < L; i++)
    {
        string[i]=get_random()%('z'-'a'+1)+'a';
        
    }
    //printf("%s  %d \n",string,L);
    string[L+1]='\0';
    return string;
}
struct nodo *genlist(struct nodo *head,struct parametri P)
{
    for (int i = 0; i < P.N; i++)
    {
    struct nodo *new_nodo=(struct nodo *)malloc(sizeof(struct nodo));
    if (new_nodo==NULL)
    {
        fprintf(stderr,"ERRORE\n");
    }
    new_nodo->string=genString();
    new_nodo->next=head;
    head=new_nodo;
   }
    return head;
}
void printlist(struct nodo *head)
{
    struct nodo *ptrhead=(struct nodo *)malloc(sizeof(struct nodo));
    ptrhead=head;
    while (ptrhead->next!=NULL)
    {
        printf("%s \n",ptrhead->string);
        if(ptrhead->next==NULL)
        {break;}
        else
        {ptrhead=ptrhead->next;}
    }

    
}
int cont(struct nodo *head,struct parametri P)
{
    //printf("ciao");
    struct nodo *point=(struct nodo *)malloc(sizeof(struct nodo));
    if (point==NULL)
    {
       fprintf(stderr,"ERRORE ALLOCAZIONE\n");
       exit(-1);
    }
    point=head;
    int cont=0;
    char *temp;
    //printf("ciao");
    while (point->next!= NULL)
    {  // printf("ciao");
    temp=point->string;
        for(int i = 0; i < strlen(temp); i++)
        {
            if (temp[i]==P.w)
            {
                cont++;
            }
            
        }
    point=point->next;
    }
    return cont;
}
struct nodo *sortList(struct nodo *head)
{
    struct nodo *ptrCurr = (struct nodo *)malloc(sizeof(struct nodo));
    struct nodo *ptrPrev = (struct nodo *)malloc(sizeof(struct nodo));
    ptrCurr=head->next;
    ptrPrev=head;
    char *temp;

    while (ptrPrev->next !=NULL) 
    { ptrCurr=ptrPrev->next;
        while (ptrCurr->next != NULL)
        {
        if(strcmp(ptrCurr->string,ptrPrev->string)<0)
         {
         //printf("ciao\n");
         temp=ptrPrev->string;
         ptrPrev->string=ptrCurr->string;
         ptrCurr->string=temp;
         }
         ptrCurr=ptrCurr->next;
        }
        ptrPrev=ptrPrev->next;
        
    }
    return head;
}