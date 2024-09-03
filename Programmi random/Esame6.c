#include <stdio.h>
#include <stdlib.h>

unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

struct stack{
    double *array;
    int top_index;
};
double genRandom();
void readInput(int argc,char *argv[],int N,int M,double x,double y);
struct stack *declaration(int N);
struct stack *push(struct stack *S1, double x, double y);
struct stack *pop(struct stack *S1);
int main(int argc,char *argv[])
{
    int N,M;
    double x,y;
    struct stack *S1;
    readInput(argc,argv,N,M,x,y);
    S1=declaration(N);


}

void readInput(int argc,char *argv[],int N,int M,double x,double y)
{
    N=atoi(argv[1]);
    if (N<20 || N>25)
    {
        fprintf(stderr,"ERROR PLEASE TRY AGAIN\n");
        exit(-1);
    }
    M=atoi(argv[2]);
    if (M<10 || M>25)
    {
        fprintf(stderr,"ERROR PLEASE TRY AGAIN\n");
        exit(-1);
    }
    x=atof(argv[3]);
    if (x<5.0 || x>10.0)
    {
        fprintf(stderr,"ERROR PLEASE TRY AGAIN\n");
        exit(-1);
    }
    y=atof(argv[4]);
    if (y<40 || y>50)
    {
        fprintf(stderr,"ERROR PLEASE TRY AGAIN\n");
        exit(-1);
    }
}
double genRandom(double x,double y)
{
    double random;
    random=(get_random()/RAND_MAX)*(y-x)+x;
    return random;
}
struct stack *declaration(int N)
{
    struct stack *S1=(struct stack *)malloc(sizeof(struct stack));
    S1->array=(double *)malloc(sizeof(double)*(N/2));
    S1->top_index=0;
    return S1;
}
struct stack *push(struct stack *S1,double x, double y)
{   
    S1->array[S1->top_index]=genRandom(x,y);
    S1->top_index++;
    return S1;
}
struct stack *pop(struct stack *S1)
{
    S1->array[S1->top_index]=0;
    return S1;

}
