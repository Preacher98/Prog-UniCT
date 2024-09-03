#pragma once
#include"Classes.h"
#include<iostream>
class Nodo 
{
    private:
    Nodo* sx;
    Nodo* dx;
    Nodo* parent;
    Autoveicolo* veicolo;

    public:
    Nodo* getSx(){return sx;};
    Nodo* getDx(){return dx;};
    Nodo* getParent(){return parent;};
    void setSx(Nodo* sx){this->sx=sx;};
    void setDx(Nodo* dx){this->dx=dx;};
    void setParent(Nodo* parent){this->parent=parent;};
    Autoveicolo* getAutoveicolo(){return veicolo;};
    void setAutoveicolo(Autoveicolo* veicolo){this->veicolo=veicolo;};
    Nodo(Autoveicolo* veicolo){this->veicolo=veicolo;};

    

};



class bst
{
private:
    Nodo* root;
public:
    Nodo* getRoot(){return root;};
    void insert(Autoveicolo* veicolo);
    void stampa_Post_Order(Nodo* root);
    Nodo* trova_Nodo(string targa);
    Nodo* minimo(Nodo* nodo);
    Nodo* successore(Nodo* nodo);
    void elimina(string targa);
    void Disintegra_nodo(Nodo* vittima);
};

void bst::Disintegra_nodo(Nodo* vittima)
{
    Nodo* f_dx=vittima->getDx();
    Nodo* f_sx=vittima->getSx();
    if (f_dx==nullptr || f_sx==nullptr)
    {
        Nodo* figlio= f_sx != nullptr ? f_sx:f_dx;
        Nodo* padre= vittima->getParent();
        if (padre==nullptr)
        {
            root=figlio;
        }else if(vittima == padre->getSx())
        {
            padre->setSx(figlio);
        }else{padre->setDx(figlio);}

        if (figlio!=nullptr)
        {
            figlio->setParent(padre);
        }
        
        
    }else
    {
        Nodo* suxx=successore(vittima);
        Disintegra_nodo(suxx);
        vittima->setAutoveicolo(suxx->getAutoveicolo());

    }
    
}

void bst::elimina(string targa){
    Nodo* tmp=trova_Nodo(targa);
    if (tmp==nullptr)
    {
        cout<<"Elemento non trovato!! "<<endl;
        return;
    }
    
}

Nodo* bst::successore(Nodo* nodo)
{
    if (nodo->getDx()==nullptr)
    { return minimo(nodo->getDx());}
    Nodo* tmp = nodo->getParent();
    while (tmp != nullptr)
    {
        if (tmp->getAutoveicolo() > nodo->getAutoveicolo())
        {
            return tmp;
        }
        
    }
    return nullptr;
    
}

Nodo* bst::minimo(Nodo* nodo)
{

    while (nodo!=nullptr)
    {
        nodo=nodo->getSx();
    }
    
    return nodo;
}

Nodo* bst::trova_Nodo(string targa)
{
    if (root==nullptr)
    {
        cout<<"Elemento non trovato !!"<<endl;
        return root;
    }
    Nodo* tmp=root;
    while (tmp!=nullptr)
    {
    if (targa==tmp->getAutoveicolo()->getTarga())
    {
        cout<<"\nIl veicolo è stato trovato:"<<endl;
        tmp->getAutoveicolo()->stampa_all();
        return tmp;
    }else if (targa<tmp->getAutoveicolo()->getTarga())
    {tmp=tmp->getSx();}else{tmp=tmp->getDx();}
    }
    
    return tmp;
}

void bst::insert(Autoveicolo* veicolo)
{
    Nodo* new_nodo = new Nodo(veicolo);
    if (root==nullptr)
    {
        root=new_nodo;
        return;
    }

    Nodo* tmp=root;
    Nodo* parent=nullptr;
    while(tmp!=nullptr)
    {
        parent=tmp;
        if (new_nodo->getAutoveicolo() < tmp->getAutoveicolo())
        {
            tmp=tmp->getSx();
        }else{tmp=tmp->getDx();}
    }

    if (new_nodo->getAutoveicolo() < parent->getAutoveicolo())
    {parent->setSx(new_nodo);}else{parent->setDx(new_nodo);}
    new_nodo->setParent(parent);
}

void bst::stampa_Post_Order(Nodo* root)
{
    if (root==nullptr)
    {
        return;
    }
    
    root->getAutoveicolo()->stampa_all();
    stampa_Post_Order(root->getSx());
    stampa_Post_Order(root->getDx());
}