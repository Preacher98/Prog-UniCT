#include<iostream>
#include<string>
using namespace std;

class Animale
{
    private:
    string nome;
    int eta;
    public:
    Animale(int eta): eta(eta){}
    int getEta();
    virtual void  faiverso();
};
int Animale::getEta(){return eta;};

class Gatto: public Animale
{
    public:
    Gatto(int eta): Animale(eta){}
};

int main()
{
    Animale a(5);
    Animale* b;
    cout<<a.getEta()<<endl;
    b=new Animale(10);
    cout<<b->getEta()<<endl;
    cout<<b<<endl;//Stampiamo l'indirizzo puntato
    cout<<&b<<endl;//stampiamo il puntatore
    //cout<<*b<<endl;
    delete b;
    return 0;

}