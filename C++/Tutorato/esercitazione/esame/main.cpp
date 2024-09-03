#include<iostream>
#include"veicolo.h"
using namespace std;
int main()
{
    veicolo* a = new Auto("cde","aer","fe",234,3);
    a->stampa();
    return 0;
}