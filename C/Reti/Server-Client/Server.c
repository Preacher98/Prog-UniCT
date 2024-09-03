/*
 ***Testo***
 Lo scopo è quello di creare due file uno client e uno server. I due programmi attraverso la gestione dei file dovranno:
 -Registrare o far fare il login agli utenti
 0 l'utente è da registrare 
 1 l'utente è gia registrato e di conseguenza dovrà controllare se lo è effettivamente.

*/

#include<stdio.h> //Libreria funzioni di I/O comprende anche la gestione dei file
#include<stdlib.h> 
#include<string.h>

void letturaRegistrazione();

int main() {
    letturaRegistrazione();
}

void letturaRegistrazione() {
    FILE *client=fopen("Client.txt","r");
    FILE *server=fopen("Server.txt","w");
    char *buffer =  malloc(sizeof(char*)*50);
   // char *nomeutente = malloc(sizeof(char*))
    size_t dim = 50;

    
    while (!feof(client))
    {
       getline(&buffer,&dim,client);
       if (strcmp(buffer,"Value: 0")==0) {
                getline(&buffer,&dim,client);
                fprintf(server,"%s",buffer);
                getline(&buffer,&dim,client);
                fprintf(server,"%s",buffer);
                getline(&buffer,&dim,client);
                fprintf(server,"%s",buffer);
                getline(&buffer,&dim,client);  
                fprintf(server,"%s",buffer);        
       } else {
        getline(&buffer,&dim,client);
        fprintf(server,"%s",buffer);
        getline(&buffer,&dim,client);
        fprintf(server,"%s",buffer);
       }
       
       

    }

fclose(client);
fclose(server);    
}