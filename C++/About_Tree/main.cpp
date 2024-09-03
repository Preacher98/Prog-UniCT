#include<iostream>
#include"BST.h"

using namespace std;

int main(){
    BST* albero = new BST();
    for (int i = 0; i < 8; i++)
    {   
        int k;
        cout<<"inserisci la chiave: ",cin>>k;
        albero->root=albero->insert(albero->root,nullptr,k);
    }
    cout<<"Pre Order: "<<endl;
    albero->pre_order(albero->root);
    cout<<"In Order: "<<endl;
    albero->in_order(albero->root);
    cout<<"Post Order: "<<endl;
    albero->post_order(albero->root);
    int k;
    Node* max = new Node();
    Node* min = new Node();
    max=albero->root;
    min=albero->root;
    max=albero->massimo(max);
    cout<<endl;
    cout<<"\tMax= "<<max->getKey()<<" padre= "<<max->parent->getKey()<<endl;
    min=albero->minimo(min);
    cout<<"\tMin= "<<min->getKey()<<" padre= "<<min->parent->getKey()<<endl;
    min=albero->minimo(albero->root->dx);
    cout<<"\tMin dx= "<<min->getKey()<<"padre= "<<min->parent->getKey()<<endl;
    cout<<endl;
    Node* temp;
    cout<<"inserisci la chiave da cercare: ",cin>>k;
    temp=albero->ricerca(albero->root,k);
    cout<<"Chiave cercata"<<temp->getKey()<<endl;
        albero->in_order(albero->root);
    return 0;
}