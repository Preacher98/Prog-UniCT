#include <stdlib.h>
#include <stdio.h>

unsigned int get_random()
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

struct inputparametres{
    int N;
    char w;
    double x,y;
};
struct Nodo
{
    char *string;
    double number;
    struct Nodo *next;
};
//Gnerazione dei prototipi delle funzioni
struct inputparametres readInput(int argc,char *argv[]);
struct Nodo *InsertHead();
struct Nodo *InsertTail();
struct Nodo *Queue(struct Nodo *Head,struct Nodo *Tail,struct inputparametres P);
char *genString(struct inputparametres P);
double genNumber(struct inputparametres P);
void printlist(struct Nodo *Head,struct Nodo *Tail,struct inputparametres P);
void printText(struct Nodo *Tail,struct Nodo *Head,struct inputparametres P);
void getText();
int main(int argc,char *argv[])
{
    struct Nodo *Head=InsertHead(),*Tail=InsertTail();
    struct inputparametres P;
    P=readInput(argc,argv);
    Tail=Queue(Head,Tail,P);
    char *string=genString(P);
    double num=genNumber(P);
    printf("%s %.2lf\n",string,num);
    printlist(Head,Tail,P);
    printText(Tail,Head,P);
    getText();
}
struct inputparametres readInput(int argc,char *argv[])
{
    struct inputparametres P;
    P.N=atoi(argv[1]);
    if (P.N<0 || P.N>15)
    {
        fprintf(stderr,"Warning !! Error !! \n");
        exit(-1);
    }
    P.w=argv[2][0];
    if (P.w<'a' || P.w>'z')
    {
        fprintf(stderr,"Warning !! Error !! \n");
        exit(-1);
    }
    P.x=atof(argv[3]);
    if (P.x<5.0 || P.x >10.0)
    {
        fprintf(stderr,"Warning !! Error !! \n");
        exit(-1);
    }
    P.y=atof(argv[4]);
    if (P.y<10.0 || P.y>30.0)
    {
        fprintf(stderr,"Warning !! Error !! \n");
        exit(-1);
    }
    
    return P;
}
struct Nodo *InsertHead()
{
    struct Nodo *Head=(struct Nodo *)malloc(sizeof(struct Nodo));
    if (Head==NULL)
    {
        printf("Errore nella creazione della testa ! \n");
    }
    return Head;   
}
struct Nodo *InsertTail()
{
    struct Nodo *Tail=(struct Nodo *)malloc(sizeof(struct Nodo));
    if (Tail==NULL)
    {
        printf("Errore nella creazione della coda ! \n");
    }
    return Tail;
}
char *genString(struct inputparametres P)
{
    int leng=get_random()%(P.N-(P.N/2)+1)+(P.N/2);
    char *string=(char *)malloc(sizeof(char*)*leng);
    for (int i = 0; i < P.N; i++)
    {
       string[i]=get_random()%('z'-'a'+1)+'a';
    }
    return string;
}
double genNumber(struct inputparametres P)
{
    double number=((double)get_random()/RAND_MAX)*(P.y-P.x)+P.x;
    return number;
}
struct Nodo *Queue(struct Nodo *Head,struct Nodo *Tail,struct inputparametres P)
{
    if(Head==NULL)
    {Head=InsertHead();}
    if(Tail==NULL)
    {Tail=InsertTail();}
    printf("ciao");
    Tail->next=Head;
    for (int i = 0; i < P.N; i++)
    {
        struct Nodo *new_nodo=(struct Nodo*)malloc(sizeof(struct Nodo));
        new_nodo->string=genString(P);
        new_nodo->number=genNumber(P);
        /*if (i==0)
        {
            Head=new_nodo;
            Head->next=NULL;
            Tail->next=Head;
        }*/

        new_nodo->next=Tail->next;
        Tail->next=new_nodo;
    }
    
return Tail;
}
void printlist(struct Nodo *Head,struct Nodo *Tail,struct inputparametres P)
{
    struct Nodo *temp=(struct Nodo *)malloc(sizeof(struct Nodo));
    temp=Tail;
    int count=0;
    while(count<P.N)
    {
        temp=temp->next;
         printf("[Nodo %d]: String=(%s) Number=(%.2lf)\n",count,temp->string,temp->number);
        
        count++;
        
    }
    
    free(temp);
    
}
void printText(struct Nodo *Tail,struct Nodo *Head,struct inputparametres P)
{
     char *mode="w+";
    const char *name="list_file.txt";
    FILE *file=fopen(name,mode);
    struct Nodo *temp=(struct Nodo *)malloc(sizeof(struct Nodo));
    temp=Tail;
    if (!file)
    {
        fprintf(stderr,"Errore nell'apertura del file ! \n");
        perror("");
    }
    int count=0;
    while (count<P.N)
    {
     temp=temp->next;
     fprintf(file,"%lf");
    }
    printf("Scrittura eseguita correttamente ! \n");
    free(temp);
    fclose(file);
    
}
void getText()
{
    char *mode="r+";
    const char *name="list_file.txt";
    FILE *fp=fopen(name,mode);
    char *string;
    size_t p=0;
    if(!fp)
    {
        fprintf(stderr,"Errore nell'apertura del file ! \n");
        perror("");
    }
    while (!feof(fp))
    {
       //fscanf(fp,"%s ",string);
       getline(string,10,fp);
       printf("%s \n",string);
    }
    fclose(fp);
}