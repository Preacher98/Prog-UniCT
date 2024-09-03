#pragma once
#include<iostream>

using namespace std;


class Nodo
{
private:

    int val;
    
public:
    Nodo* prev;
    Nodo* next;
    Nodo(Nodo* p, Nodo* n): prev(p), next(n){};
    Nodo(int v): val(v){};
    Nodo(){};
    int getVal(){return val;};
    void setVal(int v) {val=v;};
    void setPrev(Nodo* p){prev=p;};
    void setNext(Nodo* n){next=n;};
    Nodo* getNext(){return next;};
    Nodo* getPrev(){return prev;};

};
