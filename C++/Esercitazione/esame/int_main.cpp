#include<iostream>
#include<string>
#include"classes.h"
#include"coda.h"


using namespace std;


int main()
{
    Frutto* f1 = new Mela("Supermela","Ottobre","Rosso","Mela");
    Frutto* f2 = new Arancia("Aranciona","Estate","Arancione","Arancia");
    Frutto* f3 = new Mela("Melonaa","Clamoro","Rosso","Mela");
    Frutto* f4 = new Arancia("Aran","Este","Arone","Arancia");
    Coda<Frutto>* coda1 = new Coda<Frutto>();
    coda1->inserisci_nodo(f1);
    coda1->inserisci_nodo(f2);
    coda1->inserisci_nodo(f3);
    coda1->inserisci_nodo(f4);
    coda1->stampa_coda();
    coda1->stampaDim();
    coda1->elimina_in_testa();
    coda1->stampaDim();
    coda1->cancellaTipo(coda1,"Mela");
    coda1->stampa_coda();
    coda1->stampaDim();
    return 0;
    cout<<"\n\tDim= "<<coda1->getDim()<<endl;
    coda1->elimina_in_testa();
    coda1->stampa_coda();
    cout<<"\n\tDim= "<<coda1->getDim()<<endl;
    
    coda1->stampa_coda();

    return 0;
    

}