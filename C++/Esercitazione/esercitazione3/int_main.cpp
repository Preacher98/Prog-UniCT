#include<string>
#include<iostream>
#include"cittadini.h"
#include"BesseT.h"

using namespace std;

void inserisci(BST* albero);
cittadini* studente();
cittadini* lavoratore();
cittadini* pensionato();
int main()
{
    BST* albero = new BST();
    inserisci(albero);
    /*cittadini* c1 = new studenti(1,"Fabio","Iraci","Giarre",15,"Industriale");
    cittadini* c2 = new lavoratori(2,"Giovanni","Fragala","Galermo",43,"Saldatore");
    cittadini* c3 = new pensionati(3,"Antonino","Pistorio","Riposto",67,"RompiPalle");

    albero->insertNodo(c1);
    albero->insertNodo(c2);
    albero->insertNodo(c3);
    albero->stampa_InOrder(albero->getRoot());*/
    return 0;

 }

void inserisci(BST* albero)
 {
    int x=0;
    cout<<"inserisci il tipo del cittadino: "<<endl;
    cout<<"\n1)Studente (6-19) \n2)Lavoratore (20-50) \n3)Pensionato (50 in su) \n 4)Stampa \n";
    cin>>x;
    switch (x)
    {
    case 1:
        albero->insertNodo(studente());
        inserisci(albero);
        
    case 2:
        albero->insertNodo(lavoratore());
        inserisci(albero);
        
    case 3:
        albero->insertNodo(pensionato());
        inserisci(albero);
        
    case 4:
        albero->stampa_InOrder(albero->getRoot());
        break;
    default:
        break;
    }
    

 }

 cittadini* studente(){
    cittadini* c1 = new studenti(1,"Fabio","Iraci","Giarre",15,"Industriale");
    return c1;
 }

 cittadini* lavoratore()
 {
    cittadini* c2 = new lavoratori(2,"Giovanni","Fragala","Galermo",43,"Saldatore");
    return c2;
 }
cittadini* pensionato()
{
    cittadini* c3 = new pensionati(3,"Antonino","Pistorio","Riposto",67,"RompiPalle");
    return c3;
}