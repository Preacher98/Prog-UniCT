#include<iostream>
#include"Nodo.h"
using namespace std;

class List
{
private:
    Nodo* head;
    Nodo* tail;
    int num_nodo=0;
public:
    List(int num): head(NULL), tail(NULL), num_nodo(num){};
    List(){};
    void inserisci_in_testa(int v);
    void inserisci_in_coda(int v);
    void stampa();

};

void List::inserisci_in_testa(int v)
{
    Nodo* new_nodo= new Nodo(v);
    if (head==NULL)
    {
        head=new_nodo;
        tail=new_nodo;
    }else{
        new_nodo->next=head;
        head->prev=new_nodo;
        head=new_nodo;
    }
    
}

void List::stampa()
{
    Nodo* temp = new Nodo();
    temp=head;
    while (temp != NULL)
    {
        cout<<"\t Num= "<<temp->getVal()<<endl;
        temp=temp->next;
    }
    
}

void List::inserisci_in_coda(int v)
{
     Nodo* new_nodo= new Nodo(v);
     new_nodo->next=nullptr;
    if (head==NULL)
    {
        new_nodo->prev=nullptr;
        head=new_nodo;
        tail=new_nodo;
    }else{
        tail->next=new_nodo;
        new_nodo->prev=tail;
        tail = new_nodo;
    }
    
}