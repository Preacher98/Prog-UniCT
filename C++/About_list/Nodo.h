#pragma once
#include<string>
#include<iostream>

using namespace std;

class Nodo
{
public:
    Nodo* next;
    Nodo* prev;
    string nome;
    int eta;
    Nodo(Nodo* s, string str, int d): next(s), nome(str), eta(d){}
    Nodo(Nodo* s, Nodo* n): next(s), prev(n){}
    Nodo* getprev(){return prev;};
    void setprev(Nodo* p){prev=p;};
    Nodo(): next(NULL){}
    //~Nodo();
};

