#include<iostream>
#include"Classes.h"
#include"bst.h"
#include<string>

using namespace std;

int main()
{
   bst* albero = new bst();
   Autoveicolo* veicolo= new Auto("panda","non ricordo",34,"va bene cois",34,5);
   Autoveicolo* veicolo1= new Moto("moto?","credo di si",34,"really",34,"troia");
   Autoveicolo* veicolo2= new Auto("wandanator","non ricordo",34,"va bene cois",34,5);
   Autoveicolo* veicolo3= new Moto("motorinao","credo di si",34,"really",34,"troia");
    albero->insert(veicolo);
    albero->insert(veicolo1);
    albero->insert(veicolo2);
    albero->insert(veicolo3);
    
    albero->stampa_Post_Order(albero->getRoot());
    albero->trova_Nodo("wandanator");
    albero->elimina("wandanator");
    albero->stampa_Post_Order(albero->getRoot());
   return 0;
}