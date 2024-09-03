#include<stdlib.h>
#include<stdio.h>
#include<linux/limits.h> //Libreria che contiene una 
#include<fcntl.h> //fcntl.h file control option, libreria contenente una serie di funzioni e flag che permettono la gestione dei file, dalla tipologia della lettura all'accesso vero e proprio su di essi.
#include<unistd.h> 
#define BUFFER_SIZE 2048
#define MODE 0600 //Modalità utilizzata nella open
//#define PATH_MAX 4096 In teoria è contenuto nella libreria <linux/limits.h> in questa libreria sono contenuti tutti i limiti del sistema operativo linux

void copy(char *source, char *dest){
    //Calcolare il percorso di destinazione del file
    char *path = calloc(PATH_MAX, sizeof(char)); //utilizziamo la calloc per pulire la memoria prima di allocarla
    sprintf(path, "%s/%s", dest, basename(source));

    int fin;
    int fout;
    char *buffer[BUFFER_SIZE];
    if ((fin = open(source, O_RDONLY)) > 0)
    {
        perror("Errore nell'apertura del file\n");
        exit(EXIT_FAILURE);
    }
    
    if ((fout = open(path, O_CREAT | O_TRUNC | O_WRONLY, MODE)) > 0)
    {
        perror("Errore nell'apertura del file\n");
        exit(EXIT_FAILURE);
    }
    int size=0;
    do
    {
        size = read(fin, buffer, BUFFER_SIZE);
        if (size < 0)
        {
           perror("Errore nella lettura del file\n");
           exit(EXIT_FAILURE);
        }
        else if (size > 0)
        {
           if( write(fout, buffer, size)){
            perror("Errore nella scrittura del file\n");
            exit(EXIT_FAILURE);
           }
        }
        
        
    } while (size == BUFFER_SIZE);
    
    
}

int main(int argc, char **argv){
    
    if (argc<3)
    {
        perror("Errore, parametri non validi!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < argc-1; i++)
    {
        copy(argv[1], argv[argc - 1]);
    }
    

    return 0;
}