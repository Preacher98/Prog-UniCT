#pragma once
#include<iostream>
#include"Node.h"
using namespace std;
class BST
{
public:
    Node* root=nullptr;
    BST(){};
    Node* insert(Node* root,Node* padre, int k);
    void in_order(Node* root);
    void pre_order(Node* root);
    void post_order(Node* root);
    Node* minimo(Node* root);
    Node* massimo(Node* max);
    Node* ricerca(Node* root, int k);
    Node* trapianta(Node* root, Node* old_nodo, Node* nuovo);
    Node* successore(Node* n);
    
};

Node* BST::successore(Node* n)
{
    if (n->dx!=nullptr)
    {
        /* code */
    }
    
}

Node* BST::trapianta(Node* root, Node* old_nodo, Node* nuovo)
{
    
    if (old_nodo==nullptr)
    {
       root=nuovo;
    }
    
}

Node* BST::massimo(Node* max)
{
   if (max->dx==nullptr)
   {
    return max;
   }else{massimo(max->dx);};
   
    
}

Node* BST::minimo(Node* min)
{
    if (min->sx==nullptr)
    {
       return min;
    }else{minimo(min->sx);};
    
}

void BST::pre_order(Node* root)
{
    if (root == nullptr)
    {
       
       return;
    }
    cout<<"\tkey= "<<root->getKey()<<"\t||"<<endl;
    pre_order(root->sx);
    pre_order(root->dx);
}
void BST::post_order(Node* root)
{
    if (root == nullptr)
    {return;}
    post_order(root->sx);
    post_order(root->dx);
    cout<<"\tkey= "<<root->getKey()<<"\t||"<<endl;
}
Node* BST::insert(Node* root, Node* padre,int k)
{
    if (root==nullptr)
    {
        Node* new_nodo = new Node(k);
        new_nodo->parent=padre;
        return new_nodo;
    }else{
        
        if (k<root->getKey())
        {  
            root->sx=insert(root->sx,root,k);
        }else{
            
        root->dx=insert(root->dx,root,k);} 
    }
    return root;   
}

void BST::in_order(Node* root){
    if (root == nullptr)
    {
       
       return;
    }
    
    in_order(root->sx);
    cout<<"\tkey= "<<root->getKey()<<"\t||"<<endl;
    in_order(root->dx);
}

Node* BST::ricerca(Node* root, int k)
{
    if (root==nullptr)
    {
        cout<<"Nodo non trovato !"<<endl;
        return root;
    }

    if (root->getKey() == k)
    {
        cout<<"\nL'elemento è stato trovato "<<root->getKey()<<endl;
        return root;
    }else if(k<root->getKey()){
        return ricerca(root->sx,k);
        }
        else{
            return ricerca(root->dx,k);
            }
    
    
    return root;
}

/* 
Caso 1: Il nodo è una foglia quindi per eliminare il nodo basta

Caso 2: Il nodo ha 1 figlio

Caso 1 e 2: si possono raggruppare considerando che avere un figlio puo essere anche NULL


*/