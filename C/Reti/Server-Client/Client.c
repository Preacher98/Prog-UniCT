/*
 ***Testo***
 Lo scopo è quello di creare due file uno client e uno server. I due programmi attraverso la gestione dei file dovranno:
 -Registrare o far fare il login agli utenti
 0 l'utente è da registrare 
 1 l'utente è gia registrato e di conseguenza dovrà controllare se lo è effettivamente.

*/

#include<stdio.h> //Libreria funzioni di I/O comprende anche la gestione dei file
#include<stdlib.h> 

typedef struct Profilo
{
    char nome[20];
    char cognome[20];
    char password[20];
    char NomeUtente[20];
    short int value; //Questo value, simile ad un bool, serve a far capire al server se l'utente necessita di profilazione o è gia registrato
}utente;

void registrazione();
void login();
void menuClient();
void scritturaRegister(utente pers);
void scritturaLogin(utente pers);

int main() {

    
    menuClient();
    return 0;
}

void menuClient() {

    short int selector=0;
    do{
    printf("\t**Menu**\n1)Registra utente\n2)Login utente\n3)Esci\n >");
    scanf("%hd",&selector);
    }while(selector<1 || selector>3);
    switch (selector)
    {
    case 1:registrazione();
        break;
    case 2:login();
        break;
    case 3:exit(0);
        break;
    
    default:
        break;
    }
}

void registrazione() {
    
    utente persona; //istanziazione della struct

    //inseriento dati utente
    persona.value=0;
    printf("Inserisci il Nome:\n> ");
    scanf("%s",persona.nome);  
    printf("Inserisci il cognome:\n> ");
    scanf("%s",persona.cognome);
    printf("Inserisci il nome utente:\n> ");
    scanf("%s",persona.NomeUtente);
    printf("Inserisci la password:\n> ");
    scanf("%s",persona.password);
    scritturaRegister(persona);
    //printf("Hai inserito l'utente: %s, %s, %s, %s, %hd \n",persona.nome, persona.cognome, persona.NomeUtente, persona.password, persona.value);   
    
}

void scritturaRegister(utente pers) {
    
    FILE *file_R; //Creazione puntatore a file
    file_R=fopen("Client.txt","a"); //Apertura file in modalità w ovvero scrittura
    
    if (file_R==NULL) { //se ha qualche problema con l'apertura del file lo comunica immediatamente
        printf("Errore impossibile aprire il file!\n");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file_R,"Value: %hd\n",pers.value);
    fprintf(file_R,"Nome: %s\n",pers.nome);
    fprintf(file_R,"Cognome: %s\n",pers.cognome);
    fprintf(file_R,"Nome Utente: %s\n",pers.NomeUtente);
    fprintf(file_R,"Password: %s\n",pers.password);
    
    fclose(file_R);

}

void login() {

    utente temp;

    temp.value=1;   
    printf("Inserisci il nome utente: \n> ");
    scanf("%s",temp.NomeUtente);   
    printf("Inserisci la password: \n> ");
    scanf("%s",temp.password);
    scritturaLogin(temp);
    //printf("utente da login: %s, %s, %hd ",temp.NomeUtente, temp.password, temp.value);
    
}

void scritturaLogin(utente pers) {
    FILE *file_L;
    file_L=fopen("Client.txt","a");

    fprintf(file_L,"Value: %hd\n",pers.value);
    fprintf(file_L,"Nome Utente: %s\n",pers.NomeUtente);
    fprintf(file_L,"Password: %s\n",pers.password);
    
    fclose(file_L);
}