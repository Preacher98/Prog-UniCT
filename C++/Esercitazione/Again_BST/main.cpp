#include<iostream>
#include"bst.h"

using namespace std;

int main()
{
    BST<int>* albero = new BST<int>();
    albero->inserimento(10);
    albero->inserimento(4);
    albero->inserimento(5);
    albero->inserimento(7);
    albero->inserimento(12);
    albero->inserimento(15);
    albero->inserimento(18);
    albero->In_Order(albero->getRoot());
    Nodo<int>* min = albero->minimo(albero->getRoot());
    cout<<"Min= "<<min->getKey()<<endl;
    Nodo<int>* tr= albero->trovakey(15);
    cout<<"N trv = "<<tr->getKey()<<endl;
    albero->func();
    return 0;
}