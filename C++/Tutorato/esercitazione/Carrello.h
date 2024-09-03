#pragma once
#include<vector>
#include<iostream>
#include"Videogame.h"
using namespace std;

template<typename T>
class Carrello
{
private:
    vector<T*> carrello;
public:
    Carrello(){};
    void Aggiungi_Gioco(T* gioco);
    void Elimina_Gioco(T* gioco);
    void Stampa_Giochi();
    ~Carrello();
};

template<typename T>
void Carrello<T>::Aggiungi_Gioco(T* g)
{
    carrello.push_back(g);
}

template<typename T>
void Carrello<T>::Stampa_Giochi()
{
    for (T* g : carrello)
    {
        cout<<g->getTitolo()<<endl;
    }
    
}

template<typename T>
Carrello<T>::~Carrello()
{
    for(T* e : carrello)
    delete e;
}
template<typename T>
void Carrello<T>::Elimina_Gioco(T* e)
{
    for (int i = 0; i < carrello.size(); i++)
    {
        if (*e == *carrello[i])
        {
            Videogame *ptr = carrello[i];
            delete ptr;
        }
        
    }
    
}

bool sonoUguali()
{

}