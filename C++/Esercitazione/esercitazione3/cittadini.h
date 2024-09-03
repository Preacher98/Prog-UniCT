#pragma once
#include<iostream>
#include<string>

using namespace std;

class cittadini
{
    private:
    int tipo;
    string nome;
    string cognome;
    string citta;
    int anni;

    public:
    cittadini(int tipo, string nome, string cognome, string citta, int anni);
    void setNome(string nome){this->nome=nome;};
    void setCognome(string cognome){this->cognome=cognome;};
    void setCitta(string citta){this->citta=citta;};
    void setAnni(int anni){this->anni=anni;};
    void setTipo(int tipo){this->tipo=tipo;};
    string getNome(){return nome;};
    string getCognome(){return cognome;};
    string getCitta(){return citta;};
    int getAnni(){return anni;};
    int getTipo(){return tipo;};
    virtual void stampa_cittadino()=0;

};

cittadini::cittadini(int tipo, string nome, string cognome, string citta, int anni){
    this->tipo=tipo;
    this->nome=nome;
    this->cognome=cognome;
    this->citta=citta;
    this->anni=anni;
}

class studenti: public cittadini
{
    private:
    string scuola;
    public:
    studenti(int tipo, string nome, string cognome, string citta, int anni, string scuola);
    void setScuola(string scuola){this->scuola=scuola;};
    string getScuola(){return scuola;};
    void stampa_cittadino();

};

studenti::studenti(int tipo, string nome, string cognome, string citta, int anni, string scuola):cittadini(tipo,nome,cognome,citta,anni){this->scuola=scuola;}
void studenti::stampa_cittadino(){
    cout<<"Cittadino: "<<"\tTipo: "<<"\n\tNome: "<<getNome()<<"\tCognome: "<<getCognome()<<"\n\tCitta: "<<getCitta()<<"\tAnni: "<<getAnni()<<"\tScuola: "<<getScuola()<<endl;
}
class lavoratori : public cittadini
{
    private:
    string posto_lavoro;
    public:
    lavoratori(int tipo,string nome, string cognome, string citta, int anni, string posto_lavoro);
    void setPosto_lavoro(string posto_lavoro){this->posto_lavoro=posto_lavoro;};
    string getPosto_lavoro(){return posto_lavoro;};
    void stampa_cittadino();

};

lavoratori::lavoratori(int tipo, string nome, string cognome, string citta, int anni, string posto_lavoro):cittadini(tipo,nome,cognome,citta,anni){this->posto_lavoro=posto_lavoro;}
void lavoratori::stampa_cittadino(){
    cout<<"Cittadino: "<<"\n\tNome: "<<getNome()<<"\tCognome: "<<getCognome()<<"\n\tCitta: "<<getCitta()<<"\tAnni: "<<getAnni()<<"\tLavoro: "<<getPosto_lavoro()<<endl;
}
class pensionati: public cittadini
{
    private:
    string attributo_pensionato;
    public:
    void setAttributi(string attributo_pensionato){this->attributo_pensionato=attributo_pensionato;};
    string getAttributo(){return attributo_pensionato;};
    pensionati(int tipo, string nome, string cognome, string citta, int anni,string attributo_pensionato);
    void stampa_cittadino();
};
pensionati::pensionati(int tipo, string nome, string cognome, string citta, int anni,string attributo_pensionato):cittadini(tipo,nome,cognome,citta,anni){this->attributo_pensionato=attributo_pensionato;}
void pensionati::stampa_cittadino()
{
    cout<<"Cittadino: "<<"\n\tNome: "<<getNome()<<"\tCognome: "<<getCognome()<<"\n\tCitta: "<<getCitta()<<"\tAnni: "<<getAnni()<<"\tAttributo: "<<getAttributo()<<endl;
}