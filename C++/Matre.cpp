#include<iostream>
#include<algorithm>

using namespace std;

int main()
{   
    int matrice[4][4];
    string str;
    cout<<"inserisci il nome completo: "<<endl;
    getline(cin,str);
    cout<<" "<<str<<endl;
    //remove_if(str.begin(),str.end(),isspace);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
           // matrice[i][j]=i+j;
            *(*(matrice+i)+j)=i+j;
           
        }
        
       string strg[10]={};
       string capo= "suca";
       strg[1]=capo;

       int sstringa[10];
       int var=100;
       
    }
    
     for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
           // matrice[i][j]=i+j;
            ;
           cout<<*(*(matrice+i)+j)<<" ";
        }
        cout<<endl;
       
    }

     cout<<*(*(matrice+2)+1)<<" ";
    


}