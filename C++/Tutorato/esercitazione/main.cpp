#include<iostream>
#include<string>
#include"Videogame.h"
#include"Carrello.h"
using namespace std;

int main()
{
    Carrello<GiochiPC> cart1;
    GiochiPC* g1= new GiochiPC("GTA","Sparatutto","Windows",34.95,"Rockstar",2020);
    cart1.Aggiungi_Gioco(g1);
    cart1.Stampa_Giochi();
    cart1.Elimina_Gioco(g1);
    cart1.Stampa_Giochi();
    cout<<g1->getTitolo()<<g1->getGenere()<<g1->getPiattaforma()<<g1->getPrezzo()<<endl;
    return 0;
}

//