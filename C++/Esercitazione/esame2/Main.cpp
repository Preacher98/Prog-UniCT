#include<iostream>
#include<string>
#include"classes.h"
#include"double_linked_list.h"

using namespace std;

int main()
{
    veicolo* v1 = new Auto("Corolla","Toyota","CZ344AA",2013,5);
    veicolo* v2 = new Moto("MZ3","Toyota","C23gA",2034,200);
    veicolo* v3 = new Auto("unnome","suzuki","CZdv5AA",2023,3);
    veicolo* v4 = new Moto("Ninja","Kawasaki","Cnyu6A",2011,1500);
    DLL<veicolo>* dll = new DLL<veicolo>();
    dll->inserisci_in_testa(v1);
    dll->inserisci_in_testa(v2);
    dll->inserisci_in_testa(v3);
    dll->inserisci_in_testa(v4);
    dll->stampa_lista();
    cout<<endl<<endl;
    dll->trovaNodo("CZdv5AA")->getMezzo()->stampa();
    dll->elimina_elemento("CZdv5AA");
    cout<<endl<<endl;
    dll->stampa_lista();
    return 0;
}