#include <stdio.h>
#include <stdlib.h>

void inserimento();
void stampa();
void menu();

typedef struct videogioco {
    char *nome;
    char *produttore;
    float prezzo;
    struct videogioco *succ;
}video;

int main()
{
    menu();
}

void menu()
{
    int s=0;
    printf("Benvenuto nel menu \n");
    printf("1)Inserisci nuovo elemento \n 2)Stampa tutti gli elementi \n 3)Cancella un elemento \n 4)Esci \n");
    gets(s);
    switch(s)
    {
        case 1: {inserimento(); break;};
        case 2: {stampa(); break;};
        //case 3: {delet(); break; };
        //case 4: {exit(); break;};
        default: break;
    }

}
void inserimento()
{
    
   struct videogioco *element={NULL};

    printf("\ninserisci il nome del videogioco");
    *element->nome = getc(stdin);
    printf("\ninserisci il produttore");
    *element->produttore = getc(stdin);
    printf("\ninserisci il prezzo");
    *element->prezzo = getc(stdin);

    menu();
}
void stampa()
{
    video view;
    printf("\n%s",view.nome);
    printf("\n%s",view.produttore);
    printf("\n%f",view.prezzo);
    
}