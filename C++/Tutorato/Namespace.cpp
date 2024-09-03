#include<iostream>

using namespace std; //Namespace libreria standard

//NAMESPACE
namespace my_space //Mio Namespace
{
    void print_messaggio(){cout<<"Dentro namespace"<<endl;} //Funzione dentro il namespace
} 
//
int massimo(int a, int b)
{
    if (a>b) return a;
    else return b;
    //Si puo scrivere cosi
    return a>b ? a:b; //Si chiama operatore ternario [(Condizione)? vero:falso]
    
}

void print_messaggio(){cout<<"CIAOO"<<endl;}
int main()
{
    print_messaggio();
    my_space::print_messaggio();
    cout<<massimo(3,5)<<endl;
}