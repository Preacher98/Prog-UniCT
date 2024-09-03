#pragma once
#include<iostream>
#include<string>
#include"cittadini.h"

class Nodo
{
    private:
    Nodo* parent;
    Nodo* Sx;
    Nodo* Dx;
    cittadini* cittadino;
    public:
    void setParent(Nodo* Parent){this->parent=parent;};
    void setSx(Nodo* Sx){this->Sx=Sx;};
    void setDx(Nodo* Dx){this->Dx=Dx;};
    void setCittadino(cittadini* cittadino){this->cittadino=cittadino;};
    Nodo* getParent(){return parent;};
    Nodo* getSx(){return Sx;};
    Nodo* getDx(){return Dx;};
    cittadini* getCittadino(){return cittadino;};
    Nodo(cittadini* cittadino):cittadino(cittadino){};

};

class BST
{
    private:
    Nodo* root;
    public:
    void setRoot(Nodo* root){this->root=root;};
    Nodo* getRoot(){return root;};
    void insertNodo(cittadini* cittadino);
    void stampa_InOrder(Nodo* root);

};

void BST::stampa_InOrder(Nodo* root)
{
    if (root==nullptr)
    {
        return;
    }
    stampa_InOrder(root->getSx());
    root->getCittadino()->stampa_cittadino();
    stampa_InOrder(root->getDx());
}

void BST::insertNodo(cittadini* cittadino)
{
    Nodo* nuovo_nodo = new Nodo(cittadino);
    if (root==nullptr)
    {
        root=nuovo_nodo;
        return;
    }
    Nodo* tmp=root;
    Nodo* father=nullptr;
    while (tmp!=nullptr)
    {
        father=tmp;
        if(nuovo_nodo->getCittadino()<tmp->getCittadino())
        {tmp=tmp->getSx();}
        else{tmp=tmp->getDx();}
        
    }
    if (nuovo_nodo->getCittadino()<father->getCittadino())
    {father->setSx(nuovo_nodo);}else
    {father->setDx(nuovo_nodo);}

    nuovo_nodo->setParent(father);
    
}