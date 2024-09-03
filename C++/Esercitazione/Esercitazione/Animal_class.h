#pragma once
#include <string>
using namespace std;
class Animal_class
{
    private:
    string nome;
    string razza;
    int eta;

    public:
    Animal_class(string n, string r, int e): nome(n), razza(r), eta(e){};
    Animal_class():nome("no_name"), razza("n/a"),eta(0){};
    void setNome(string n){nome=n;};
    string getNome(){return nome;};
    void setRazza(string r){razza=r;};
    string getRazza(){return razza;};
    void setEta(int e){eta=e;};
    int getEta(){return eta;};
    void stampa_animale(){cout<<"Nome= "<<nome<<" Razza= "<<razza<<" Eta= "<<eta<<endl;};
    virtual void verso()=0;
    bool operator==(Animal_class& a){return this->nome == a.getNome();};
    virtual Animal_class operator=(const Animal_class& op)=0;
};