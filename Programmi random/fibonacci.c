#include <stdio.h>
#include <stdlib.h>

long int fibonacci(long int);
int main()
{
    long int x=0;
    long int result=0;
    do{
        printf("inserisci il numero:");
        scanf("%ld",&x);
    }while(x<=1);
    result=fibonacci(x);
    printf("result=%ld\n",result);
}

long int fibonacci(long int x )
{
    long int fib[x];
    long int n=2;
    fib[0]=0;
    fib[1]=1;
    fib[2]=1;
     while(n<=x){
        fib[n]=fib[n-1]+fib[n-2];
        printf("n=%ld pos=%ld\n",fib[n],n);
        n++;
    }
    
long int result=fib[x];
    return result;
}
