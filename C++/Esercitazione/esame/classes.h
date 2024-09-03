#pragma once
#include<iostream>
#include<string>

using namespace std;

class Frutto
{
    private:
    string nome;
    string stagione;
    string colore;
    string tipo;
    public:
    Frutto(string nome,string stagione,string colore, string tipo):nome(nome),stagione(stagione),colore(colore), tipo(tipo){}
    void setNome(string nome){this->nome=nome;};
    void setStagione(string stagione){this->stagione=stagione;};
    void setColore(string colore){this->colore=colore;};
    string getNome(){return nome;};
    string getStagione(){return stagione;};
    string getColore(){return colore;};
    void setTipo(string tipo){this->tipo=tipo;};
    string getTipo(){return tipo;};
    void stampa();
    virtual void sapore()=0;
    
};
void Frutto::stampa()
{
    cout<<"Frutto: "<<endl<<"\tNome: "<<getNome()<<" \tStagione: "<<getStagione()<<" \tColore: "<<getColore()<<endl;
}

class Mela: public Frutto
{
    

    public:
    Mela(string nome,string stagione,string colore, string tipo):Frutto(nome,stagione,colore,tipo){}
    string getTipo();
    void sapore(){cout<<"\tSapore Molto dolce"<<endl;};
};

class Arancia: public Frutto
{ 
    public:
    Arancia(string nome,string stagione,string colore, string tipo):Frutto(nome,stagione,colore,tipo){}
    void sapore(){cout<<"\tSapore Super Amaro"<<endl;}
};


