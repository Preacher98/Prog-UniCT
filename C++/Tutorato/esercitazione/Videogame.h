#pragma once
#include<string>
using namespace std;
class Videogame
{
protected:
    string titolo;
    string genere;
    double prezzo;
    string piattaforma;
public:
    Videogame(string t, string g, string p, double price): titolo(t), genere(g), piattaforma(p), prezzo(price){};
    virtual ~Videogame()=0;
    string getTitolo(){return titolo;};
    string getGenere(){return genere;};
    string getPiattaforma(){return piattaforma;};
    double getPrezzo(){return prezzo;};
    void setTitolo(string t){titolo=t;};
    void setGenere(string g){genere=g;};
    void setPiattaforma(string p){piattaforma=p;};
    bool operator==(const Videogame& obj);

};
Videogame::~Videogame(){};
bool Videogame::operator==(const Videogame& obj)
{
    if (this->titolo == obj.titolo && this->genere == obj.genere && this->piattaforma == obj.piattaforma)
    {
        return true;
    }else false;
    

}

class GiochiPC: public Videogame
{
    private:
    string casaProduttrice;
    int annoUscita;
    public:
    GiochiPC(string t, string g,  string p, double pr, string casaP, int annoU):
    Videogame(t,g,p,pr), casaProduttrice(casaP), annoUscita(annoU){};
};

class GiochiConsole: public Videogame
{
    private:
    string casaProduttrice;
    int annoUscita;
    public:
    GiochiConsole(string titolo, string genere, double prezzo, string piattaforma, string casaProduttrice, int annoUscita):
    Videogame(titolo,genere,piattaforma,prezzo), casaProduttrice(casaProduttrice), annoUscita(annoUscita){};
};

class GiochiMobile: public Videogame
{
    private:
    string casaProduttrice;
    int annoUscita;
    public:
    GiochiMobile(string titolo, string genere, double prezzo, string piattaforma, string casaProduttrice, int annoUscita):
    Videogame(titolo,genere,piattaforma,prezzo), casaProduttrice(casaProduttrice), annoUscita(annoUscita){};
};