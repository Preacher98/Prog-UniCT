#include<iostream>
#include"Nodo.h"
#include"List.h"

using namespace std;

void menu(List* lista);
int main()
{
    List* lista = new List();
    menu(lista);

}
void menu(List* lista)
{
    
    int s,v;
    cout<<"Menu\n 1)testa \n 2)coda \n3)stampa \n4)exit \n",cin>>s;

    switch (s)
    {
    case 1:
    cout<<"inserisci il numero= ",cin>>v,cout<<endl;
    lista->inserisci_in_testa(v);
    menu(lista);
        break;
    case 2:
    cout<<"inserisci il numero= ",cin>>v,cout<<endl;
    lista->inserisci_in_coda(v);
    menu(lista);
        break;
    case 3:
    lista->stampa();
    menu(lista);
        break;
    case 4:
        break;
    
    default:
        break;
    }
}
