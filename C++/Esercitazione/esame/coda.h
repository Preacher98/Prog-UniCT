#pragma once
#include"classes.h"
#include<iostream>
#include "map"

using namespace std;

template<typename T>
class Nodo
{
    private:
    Nodo<T>* next=nullptr;
    T* f;
    public:
    Nodo(T* f):f(f){};
    Nodo<T>* getNext(){return next;};
    T* getF(){return f;};
    void setNext(Nodo<T>* next){this->next=next;};
    void setF(T* f){this->f=f;};
};

template<typename T>
class Coda
{
    private:
    Nodo<T>* head;
    Nodo<T>* tail;
    int dimensione=0;
    map<string,int> contatore_tipo;


    public:
    Nodo<T>* getHead(){return head;};
    Nodo<T>* getTail(){return tail;};
    void setHead(Nodo<T>* head){this->head=head;};
    void setTail(Nodo<T>* tail){this->tail=tail;};
    void incrDim(){dimensione++;};
    void decrDim(){dimensione--;};
    int getDim(){return dimensione;};
    void inserisci_nodo(Frutto* f);
    void stampa_coda();
    void elimina_in_testa();
    void cancellaTipo(Coda<Frutto>* coda, string tipo);
    void stampaDim();
    
};

template<typename T>
void Coda<T>::stampaDim()
{
    for(auto it = contatore_tipo.begin(); it != contatore_tipo.end(); ++it)
    {
        cout << it->first << " => " << it->second << '\n';
    }

}

template<typename T>
void Coda<T>::cancellaTipo(Coda<Frutto>* coda, string tipo)
{
   
    Nodo<T>* temp = coda->getHead();
    while (temp!=nullptr)
    {
         if (contatore_tipo.at(tipo)==0)
        {
         break;
    
        if (temp->getF()->getTipo()==tipo)
        {
            elimina_in_testa();
            
        }
        temp=temp->getNext();
        }
        temp=temp->getNext();
    }
    

    
   
}
template<typename T>
void Coda<T>::elimina_in_testa()
{
    Nodo<T>* tmp = getHead();

    setHead(tmp->getNext());
    contatore_tipo[tmp->getF()->getTipo()]-=1;
    delete tmp;
    decrDim();
    
}

template<typename T>
void Coda<T>::inserisci_nodo(Frutto* f)
{
    Nodo<Frutto>* nuovo_nodo = new Nodo<Frutto>(f);
    if (contatore_tipo.count(f->getTipo())!=1)
    {
        contatore_tipo[f->getTipo()]=0;
    }


    contatore_tipo[f->getTipo()]+=1;
    if (getHead()==nullptr && getTail()==nullptr)
    {

        setHead(nuovo_nodo);
        setTail(nuovo_nodo);
        incrDim();

    }else
    {
        getTail()->setNext(nuovo_nodo);
        setTail(nuovo_nodo);
        incrDim();
    }
    
}

template<typename T>
void Coda<T>::stampa_coda()
{
    Nodo<Frutto>* tmp=getHead();
    while (tmp!=nullptr)
    {
        tmp->getF()->stampa();
        tmp->getF()->sapore();
        tmp=tmp->getNext();
    }
    

}