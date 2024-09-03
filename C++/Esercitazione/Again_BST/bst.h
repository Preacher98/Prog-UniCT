#pragma once
#include<iostream>

using namespace std;

template<typename T>
class Nodo
{
private:
    Nodo<T>* sx=nullptr;
    Nodo<T>* dx=nullptr;
    Nodo<T>* parent=nullptr;
    T key;
public:
   Nodo(T key): key(key),sx(nullptr),dx(nullptr),parent(nullptr){};
   Nodo<T>* getSx(){return sx;};
   Nodo<T>* getDx(){return dx;};
   Nodo<T>* getParent(){return parent;};
   T getKey(){return key;};
   void setSx(Nodo<T>* sx){this->sx=sx;};
   void setDx(Nodo<T>* dx){this->dx=dx;};
   void setParent(Nodo<T>* parent){this->parent=parent;};
   void setKey(T key){this->key=key;};   
};

template<typename T>
class BST
{
    private:
    Nodo<T>* root;
    int dim;
    bool isEmpty(){return root==nullptr;};
    public:
    BST():root(nullptr),dim(0){};
    Nodo<T>* getRoot(){return root;};
    void setRoot(Nodo<T>* root){this->root=root;};
    void inserimento(T key);
    void In_Order(Nodo<T>* nodo);
    Nodo<T>* minimo(Nodo<T>* nodo);
    Nodo<T>* trovakey(T key);
    void func();

};

template<typename T>
void BST<T>::func()
{
    Nodo<T>* ptr = getRoot();
    while (ptr->getParent())
    {
        cout<<ptr->getKey()<<endl;
    }
    while(ptr)
    {
       cout<<ptr->getKey()<<endl;
       ptr=ptr->getDx();
    }
    
}


template<typename T>
Nodo<T>* BST<T>::trovakey(T key)
{
    Nodo<T>* tmp = getRoot();
    while (tmp != nullptr)
    {
    if (tmp->getKey() == key)
    {return tmp;}else if (key < tmp->getKey())
        {tmp=tmp->getSx();}else tmp=tmp->getDx();
    }
    return nullptr;    
}

template<typename T>
Nodo<T>* BST<T>::minimo(Nodo<T>* nodo)
{
    Nodo<T>* min = nodo;
    while (min->getSx()!=nullptr)
    {
       min=min->getSx();
    }
    return min;
}

template<typename T>
void BST<T>::In_Order(Nodo<T>* nodo)
{
    
    if (nodo == nullptr)
    {
        return;
    }
    In_Order(nodo->getSx());
    cout<<"Element: "<<nodo->getKey()<<endl;
    In_Order(nodo->getDx());
}

template<typename T>
void BST<T>::inserimento(T key)
{
    Nodo<T>* nuovo_nodo = new Nodo<T>(key);
    if (isEmpty())
    {
       root=nuovo_nodo;
       return;
    }
    
    Nodo<T>* tmp = getRoot();
    Nodo<T>* parent = nullptr;
    while (tmp != nullptr)
    {
        parent=tmp;
        if (nuovo_nodo->getKey()<tmp->getKey())
        {tmp=tmp->getSx();}else{tmp=tmp->getDx();}   
    }

    if (nuovo_nodo->getKey()<parent->getKey())
    {
        parent->setSx(nuovo_nodo);
    }else{parent->setDx(nuovo_nodo);}

    nuovo_nodo->setParent(parent);
    
}
