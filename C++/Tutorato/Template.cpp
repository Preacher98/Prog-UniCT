#include<iostream>

using namespace std;

template<typename T>
T massimo(T a, T b)
{
    cout<<"template generico"<<endl;
    return a>b? a:b;
}
template<>
int massimo(int a, int b)
{
    cout<<"Template int"<<endl;
    return a>b? a:b;
}

//Template classe
template<typename T, typename U>
class my_class
{
private:
    T a;
    U b;
public:
    my_class(T val1, U val2): a(val1), b(val2){};
    T getA();
    U getB();
};
//è agganciata anche ai tipi
template<typename T, typename U>
T my_class<T,U>::getA(){return a;};

int main()
{
    cout<<massimo(4.5,3.2)<<endl;
    cout<<massimo(50,33)<<endl;
    my_class<int,int> temp(2,4);
    cout<<"num: "<<temp.getA()<<endl;
}
//Usando il template non ho bisogno di specificare il tipo
