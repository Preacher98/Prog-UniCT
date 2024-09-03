#pragma once
#include<iostream>
#include<string>

using namespace std;

class veicolo
{
private:
    string nome;
    string marca;
    string codice;
    int anno;
public:
    string getNome(){return nome;}
    string getMarca(){return marca;}
    string getCodice(){return codice;}
    int getAnno(){return anno;}
    void setNome(string nome){this->nome=nome;}
    void setMarca(string marca){this->marca=marca;}
    void getCodice(string codice){this->codice=codice;}
    void getAnno(int anno){this->anno=anno;}
    virtual void stampa()=0;
    veicolo(string nome, string marca, string codice, int anno);
    ~veicolo();
};

veicolo::veicolo(string nome, string marca, string codice, int anno)
{
    this->nome=nome;
    this->marca=marca;
    this->codice=codice;
    this->anno=anno;
}
veicolo::~veicolo()
{
    nome="\0";
    marca="\0";
    codice="\0";
    anno=0;
}
class Auto: public veicolo
{
private:
    int n_passeggeri;
public:
    int getPasseggeri(){return n_passeggeri;}
    void setPasseggeri(int n_passeggeri){this->n_passeggeri=n_passeggeri;}
    void stampa();
    Auto(string nome, string marca, string codice, int anno, int n_passeggeri):veicolo(nome,marca,codice,anno){this->n_passeggeri=n_passeggeri;}
};

void Auto::stampa()
{
    cout<<"Veicolo: "<<typeid(Auto).name()<<"\n\tNome: "<<getNome()<<"\tMarca: "<<getMarca()<<"\tCodice: "<<getCodice()<<"\tAnno: "<<getAnno()<<"\tN_Pass: "<<getPasseggeri()<<endl;
}

class Moto: public veicolo
{
    private:
    int cilindrata;
    public:
    int getCilindrata(){return cilindrata;}
    void setCilindrata(int cilindrata){this->cilindrata=cilindrata;}
    void stampa();
    Moto(string nome, string marca, string codice, int anno, int cilindrata):veicolo(nome,marca,codice,anno){this->cilindrata=cilindrata;};
    
};

void Moto::stampa()
{
    cout<<"Veicolo: "<<typeid(Moto).name()<<"\n\tNome: "<<getNome()<<"\tMarca: "<<getMarca()<<"\tCodice: "<<getCodice()<<"\tAnno: "<<getAnno()<<"\tCilindrata: "<<getCilindrata()<<endl;

}
