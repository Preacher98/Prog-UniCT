#pragma once
#include "Animal_class.h"
using namespace std;
class Cat_class: public Animal_class
{
    public:
    Cat_class(string n, string r, int e):Animal_class(n,r,e){};
    void verso(){cout<<"Hi there i'm a cat !! But i don't speak i only say MiaO ! "<<endl;};
    Cat_class* operator=(const Cat_class& op)
    {
        this->setNome(op.getNome());
        this->setRazza(op.getRazza());
        this->setEta(op.setEta());
        return this;
    }
};