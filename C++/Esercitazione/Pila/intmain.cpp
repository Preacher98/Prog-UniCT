#include<iostream>
#include"class.h"

using namespace std;

int main()
{
    Pila<int>* nuova_pila = new Pila<int>();
    nuova_pila->Push(4);
    nuova_pila->Push(3);
    nuova_pila->Push(1);
    nuova_pila->Push(6);
    nuova_pila->Push(7);
    nuova_pila->stampa();
    nuova_pila->Pop();
    nuova_pila->Pop();
    cout<<endl;
    nuova_pila->stampa();
    cout<<endl;
    Pila<double>* new_pila = new Pila<double>();
    new_pila->Push(3.56);
    new_pila->Push(4.78);
    new_pila->Push(7.66);
    new_pila->Push(1.45);
    new_pila->Push(3.66);
    new_pila->stampa();
    cout<<endl;
    
    return 0;
}