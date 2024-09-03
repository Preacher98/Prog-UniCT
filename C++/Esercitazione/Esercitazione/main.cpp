#include <string>
#include <iostream>
#include "Animal_class.h"
#include "Cat_class.h"
#include "Dog_class.h"
#include "BST_class.h"
using namespace std;
int main()
{
    cout<<"Ciao"<<endl;
    Cat_class* gatto1 = new Cat_class("Felix","Persiano",13);
    Cat_class* gatto2 = new Cat_class("FAbrozop","Pers",11); 
    gatto1->stampa_animale();
    gatto2->stampa_animale();
    gatto1->verso();
    gatto2->verso();
    BST_class* tree = new BST_class();
    tree->insert_node(tree->getRadice(),gatto1);
    tree->print_BST(tree->getRadice());
    return 0;
}