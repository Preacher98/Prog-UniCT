#include<iostream>
#include<string>
#include"Nodo.h"

using namespace std;

void menu();
Nodo* crealista();
int main()
{
    int n=0,age=0,tmp=0;
    string str;
    Nodo* head = new Nodo();
    cout<<"Quanti nodi vuoi inserire ?"<<endl,cin>>n;
    for (int i = 0; i < n; i++)
    {
        cout<<"Inserisci il nome dell'utente: ",cin>>str;
        cout<<"\nInserisci l'età: ",cin>>age;
        Nodo* new_nodo = new Nodo(new_nodo,str,age);
        new_nodo->setprev(new_nodo);
        head=new_nodo;

    }
    Nodo* tmp_nodo = new Nodo();
        tmp_nodo=head;
    for (int i = 0; i < n; i++)
    {
        cout<<"\t"<<tmp_nodo->nome<<"\t "<<tmp_nodo->eta<<endl;
        tmp_nodo=tmp_nodo->next;
        /*if (tmp_nodo==NULL)
        {delete tmp_nodo;}*/
        
    }
        tmp_nodo=head;
    cout<<"inserisci l'elemento da cercare: ",cin>>tmp;
    bool flag=false;
    while (tmp_nodo->next != NULL)
    {
        if (tmp_nodo->eta == tmp)
        {
            cout<<"Inserisci il nome dell'utente: ",cin>>str;
            cout<<"\nInserisci l'età: ",cin>>age;
            Nodo* new_nodo = new Nodo(new_nodo,str,age);
            new_nodo->next=tmp_nodo->next;
            tmp_nodo->next=new_nodo;
            n++;
            flag=true;
        }else if(flag==true){break;}

        tmp_nodo=tmp_nodo->next;
    }
    tmp_nodo=head;
    for (int i = 0; i < n; i++)
    {
        cout<<"\t"<<tmp_nodo->nome<<"\t "<<tmp_nodo->eta<<endl;
        tmp_nodo=tmp_nodo->next;
        
    }

    
}

void menu()
{
    int s;
    do
    {
       cout<<"\tMenù"<<"\n1)Crea lista \n2)Modifica lista \n3)Esci",cin>>s; 
    } while (s<0 || s>3);
    
    switch (s)
    {
    case 1: 
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
    
    
}

Nodo* crealista()
{
    
}