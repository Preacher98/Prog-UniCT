#include<stdlib.h>
#include<stdio.h>
struct conca
{
    int valore;
};

struct nodo{    
    struct conca d;
    struct nodo* next;
};



void printlist(struct nodo *p);
void inserimento(struct nodo** new);
void menu(struct nodo* testa);
void elimina_elemento(struct nodo** head);

int main()
{
    
    struct nodo* testa;
    menu(testa);

}
void inserimento(struct nodo** testa)
{
    struct nodo* novo=(struct nodo *)malloc(sizeof(struct nodo));;
    novo->next=(*testa);
    printf("inserisci il valore:");
    scanf("%d",&novo->d.valore);
    (*testa)=novo;
    //system("clear");
    menu(novo);
    

}
void printlist(struct nodo *p)
{
    while(p != NULL)
    {
        if(p != NULL)
        printf("[%d]\n",p->d.valore);
        else
        printf("\n LA LISTA E' VUOTA!!\n");

        p=p->next;

    }
    menu(p);
    
}
void menu(struct nodo* testa)
{
    int i=0;
    printf("1)Inserisci \n2)Stampa\n3)Elimina elemento\n4)exit\n");
    scanf("%d",&i);

    switch(i)
    {
        case 1: inserimento(&testa); break;
    
        case 2: printlist(testa); break;
        
        case 3: elimina_elemento(&testa); break;
        
        case 4: exit(1); break;

        default: menu(testa); break;
    }
}
void elimina_elemento(struct nodo** head)
{
    struct nodo* pre=NULL;
    struct nodo* temp=(*head);
    int tempo=0;
    printf("inserisci il valore da eliminare");
    scanf("%d",&tempo);
    while(temp != NULL)
    {
        if(temp->d.valore==tempo)
        {
            pre->next=temp->next;
            pre=temp;
            
            free(temp);
        }
        temp=temp->next;
    }
   
    menu(*head);
}