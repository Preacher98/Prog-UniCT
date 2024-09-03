#pragma once
#include<iostream>

using namespace std;

template<typename T>
class Nodo
{
    private:
    Nodo<T>* next;
    T elemento;
    public:
    Nodo(Nodo<T>* next, T elemento):next(next),elemento(elemento){};
    Nodo(T* elemento): elemento(elemento), next(nullptr){};
    Nodo<T>* getNext(){return next;};
    T getElemento(){return elemento;};
    void setNext(Nodo<T>* next){this->next=next;};
    void setElemento(T elemento){this->elemento=elemento;};
};


template<typename T>
class Pila
{
    private:
    Nodo<T>* head;
    int dim;
    bool isEmpty(){return head==nullptr;};
    public:
    Pila():head(nullptr),dim(0){};
    void Push(T elemento);
    T Pop();
    void stampa();
};

template<typename T>
void Pila<T>::stampa()
{
    Nodo<T>* tmp = head;
    while (tmp!=nullptr)
    {
        cout<<"Elemento: "<<tmp->getElemento()<<endl;
        tmp=tmp->getNext();
    }
    
}

template<typename T>
void Pila<T>::Push(T elemento)
{
    Nodo<T>* nuovo_nodo = new Nodo<T>(head,elemento);
    head=nuovo_nodo;
    dim++;
}

template<typename T>
T Pila<T>::Pop()
{
    if(isEmpty())
    {
        cout<<"La pila è vuota ! "<<endl;
        return 0;
    }

    Nodo<T>* tmp = head;
    T temp = head->getElemento();
    head=head->getNext();
    delete tmp;
    return temp;
    
}