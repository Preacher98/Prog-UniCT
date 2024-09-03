#pragma once
#include<iostream>
#include<string>
#include"classes.h"

using namespace std;

template<typename T>
class Nodo
{
private:
    Nodo<T>* next=nullptr;
    Nodo<T>* prev=nullptr;
    T* mezzo;
public:
    Nodo<T>* getNext(){return next;}
    Nodo<T>* getPrev(){return prev;}
    veicolo* getMezzo(){return mezzo;}
    void setNext(Nodo<T>* next){this->next=next;}
    void setPrev(Nodo<T>* prev){this->prev=prev;}
    void setMezzo(T* mezzo){this->mezzo=mezzo;}
    Nodo(Nodo<T>* next, Nodo<T>*prev, T* mezzo);
    Nodo(T* mezzo):mezzo(mezzo){}
};

template<typename T>
Nodo<T>::Nodo(Nodo<T>* next, Nodo<T>*prev, T* mezzo)
{
    this->next=next;
    this->prev=prev;
    this->mezzo=mezzo;
}

template<typename T>
class DLL
{
private:
    Nodo<T>* head=nullptr;
    Nodo<T>* tail=nullptr;
    int dimensione=0;
public:
    Nodo<T>* getHead(){return head;}
    Nodo<T>* getTail(){return tail;}
    int getDim(){return dimensione;}
    void setHead(Nodo<T>* head){this->head=head;}
    void setTail(Nodo<T>* tail){this->tail=tail;}
    void incrDim(){dimensione++;}
    void decrDim(){dimensione--;}
    void inserisci_in_testa(T* veicolo);
    void stampa_lista();
    void elimina_elemento(string codice);
    Nodo<T>* trovaNodo(string codice);
};

template<typename T>
void DLL<T>::elimina_elemento(string codice)
{
    Nodo<T>* tmp=trovaNodo(codice);

    tmp->getNext()->setPrev(tmp->getPrev());
    tmp->getPrev()->setNext(tmp->getNext());

    delete tmp;
}

template<typename T>
Nodo<T>* DLL<T>::trovaNodo(string codice)
{
   Nodo<T>* tmp = getHead();
   while (tmp != nullptr)
   {
    if (tmp->getMezzo()->getCodice() == codice)
    {
        return tmp;
    }
    tmp = tmp->getNext();
   }
   if (tmp==nullptr)
   {
    cout<<"Elemento non trovato !!"<<endl;
    return tmp;
   }
    
}

template<typename T>
void DLL<T>::inserisci_in_testa(T* veicolo)
{
    
    if(getHead()==nullptr && getTail()==nullptr)
    {
        Nodo<T>* new_nodo = new Nodo<T>(veicolo);
        setHead(new_nodo);
        setTail(new_nodo);
    }else{

        Nodo<T>* new_nodo = new Nodo<T>(veicolo);
        new_nodo->setNext(getHead());
        getHead()->setPrev(new_nodo);
        setHead(new_nodo);
    }
    
}

template<typename T>
void DLL<T>::stampa_lista()
{
    Nodo<T>* temp= getHead();
    while (temp != nullptr)
    {
        temp->getMezzo()->stampa();
        temp=temp->getNext();
    }
    
}
