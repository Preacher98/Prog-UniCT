#include<iostream>
#include<string>
#include<vector>

using namespace std;



int main()
{
   vector<int> vettore;

   for (int i = 0; i < 5; i++)
   {
    int x;
    cout<<"inserisci: ",cin>>x;
    vettore.push_back(x);
   }
   for (int i = vettore.size(); i >= 0; i--)
   {
    cout<<"elemento: "<<vettore[i]<<endl;
   }
   
    
}
