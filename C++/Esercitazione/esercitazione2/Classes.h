#pragma once
#include <iostream>
#include <string>

using namespace std;

class Autoveicolo
{
    private:
    string targa;
    string nome_modello;
    int anno_fab;
    string marca;
    int cilindrata;

    public:
    Autoveicolo(string targa,string nome_modello, int anno_fab, string marca, int cilindrata);
    void setTarga(string targa){this->targa=targa;};
    void setNome_modello(string nome_modello){this->nome_modello=nome_modello;};
    void setAnno_fab(int anno_fab){this->anno_fab=anno_fab;};
    void setMarca(string marca){this->marca=marca;};
    void setCilindrata(int cilindrata){this->cilindrata=cilindrata;};
    string getTarga(){return targa;};
    string getNome_modello(){return nome_modello;};
    string getMarca(){return marca;};
    int getAnno_fab(){return anno_fab;};
    int getCilindrata(){return cilindrata;};
    virtual void stampa_all()=0;
    friend bool operator<(const Autoveicolo& v1, const Autoveicolo& v2){return v1.targa.compare(v2.targa)<0;}
    friend bool operator==(const Autoveicolo& v1, const Autoveicolo& v2){return v1.targa.compare(v2.targa)==0;}
};

Autoveicolo::Autoveicolo(string targa,string nome_modello, int anno_fab, string marca, int cilindrata){
    this->targa=targa;
    this->nome_modello=nome_modello;
    this->anno_fab=anno_fab;
    this->marca=marca;
    this->cilindrata=cilindrata;
}

class Auto: public Autoveicolo
{
    private:
    int num_porte;

    public:
    void stampa_all(){
        cout<<"Veicolo: \n"<<"\tTarga: "<<getTarga()<<"\tNome modello: "<<getNome_modello()
        <<"\n\tanno fabbricazione: "<<getAnno_fab()<<"\tMarca: "<<getMarca()<<"\tCilindrata: "<<getCilindrata()<<"Num porte: "<<num_porte<<endl;
            };
    Auto(string targa,string nome_modello, int anno_fab, string marca, int cilindrata, int num_porte);
};
Auto::Auto(string targa,string nome_modello, int anno_fab, string marca, int cilindrata, int num_porte):
Autoveicolo(targa, nome_modello, anno_fab, marca, cilindrata)
{this->num_porte=num_porte;}

class Moto: public Autoveicolo
{
    private:
    string tipo_moto;

    public:
    void stampa_all();
    Moto(string targa,string nome_modello, int anno_fab, string marca, int cilindrata, string tipo_moto):
    Autoveicolo(targa, nome_modello, anno_fab, marca, cilindrata)
    {this->tipo_moto=tipo_moto;}
};
void Moto::stampa_all(){
    cout<<"Veicolo: \n"<<"\tTarga: "<<getTarga()<<"\tNome modello: "<<getNome_modello()
        <<"\n\tanno fabbricazione: "<<getAnno_fab()<<"\tMarca: "<<getMarca()<<"\tCilindrata: "<<getCilindrata()<<"Tipo moto: "<<tipo_moto<<endl;
}