#include<iostream>
 using namespace std;

int ricorsione_Max(int *array,int dim,int max);
 int main()
 {  
    int array[5]={33,3,4,5,12};
    int dim=4;
    int max=array[dim];
    max=ricorsione_Max(array,dim,max);
    cout<<"num: "<<max;

 }

 int ricorsione_Max(int *array,int dim,int max)
 {
    
    if (dim==0)
    {
        return max;
    }
    
    if (max>array[dim-1])
    {
        cout<<"ciao"<<max;
        ricorsione_Max(array,dim-1,max);

    }else {max=array[dim]; ricorsione_Max(array,dim-1,max);}
    return max;
    
 }