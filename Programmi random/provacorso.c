#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i=-2;
    int v[5]={0,1,2,3,4};
    while(i<5)
    {
        i++;
        v[i]=10*v[i];
        printf("%d ",v[i]);
        
        
    }
}