#pragma once 
#include<iostream>
#include<string>
using namespace std;
class veicolo
{
private:
    string targa;
    string marca;
    string nome_modello;
    int anno_fabbricazione;


public:
    veicolo(string tar, string mar, string nome, int anno);
    string getTarga(){return targa;};
    string getMarca(){return marca;};
    string getNomeMod(){return nome_modello;};
    int getAnno(){return anno_fabbricazione;};
    virtual void stampa()=0;
    ~veicolo();
};
veicolo::veicolo(string tar, string mar, string nome, int anno)
{
    targa=tar;
    marca=mar;
    nome_modello=nome;
    anno_fabbricazione=anno;
}

class Auto: public veicolo
{
private:
    int num_porte;
public:
Auto(string tar, string nome, string mar,int anno, int numP): veicolo(tar,mar,nome,anno){this->num_porte=numP;};
void stampa();
};
void Auto::stampa()
{
    cout<<"Auto: \n"<<"\t"<<getNomeMod()<<"\t\n"<<getMarca()<<"\t\n"<<getTarga()<<"\t\n"<<getAnno()<<"\t\n"<<endl;
}

class moto: public veicolo
{
private:
    string tipo;
public:
    moto(string tar, string nome, string mar,int anno,string t):veicolo(tar,mar,nome,anno){this->tipo=t;};
    
};



