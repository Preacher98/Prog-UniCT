#pragma once
#include<iostream>
#include"veicolo.h"
using namespace std;

class bst
{
private:
    Nodo* root;
public:
    bst(/* args */);
    ~bst();
};

bst::bst(/* args */)
{
}

bst::~bst()
{
}

class Nodo
{
    private:
        Nodo* sx;
        Nodo* dx;
        veicolo* v;
    public:
        Nodo(veicolo* ve): v(ve){}


};
