#include<stdlib.h>
#include<stdio.h>
#include<linux/limits.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#define BUFFER_SIZE 2048
#define MODE 0600
//#define PATH_MAX 4096 In teoria è contenuto nella libreria <linux/limits.h> in questa libreria sono contenuti tutti i limiti del sistema operativo linux

void copy(char *source, char *dest){
    
    char path_destination[PATH_MAX];
    strcpy(path_destination, dest);
    strcat(path_destination, "/");
    strcpy(path_destination, basename(source));

    struct stat statbuf;
    if(lstat(source, &statbuf)==-1){ //La funzione lstat dato un ingresso, va a popolare una struct di tipo stat. Anche l'orario di creazione

    }
    
    if (S_ISDIR(statbuf.st_mode))
    {
        /*è una directory*/
        //Spoiler i file e le cartelle vengono gestite allo stesso modo, una cartella è una sequenza di file
       if ( mkdir(path_destination, 077)<0)
       {
            perror("Errore nella creazione della cartella\n");
            exit(EXIT_FAILURE);
       }
       DIR* dpout = opendir(path_destination);
       if (dpout == NULL){
        perror("Errore nell'apertura della cartella\n");
        exit(EXIT_FAILURE);
       }
       DIR* dpin = opendir(source);
       if (dpin == NULL){
        perror("Errore nell'apertura della cartella\n");
        exit(EXIT_FAILURE);
       }

       int size;
       char buffer[BUFFER_SIZE];
    do
    {
        size = readdir(dpin);
        if (size < 0)
        {
            perror("Errore nella letturapisello\n");
            exit(EXIT_FAILURE);
        }
        if (size > 0)
        {
            if (writedir(dpout, buffer, size)<0)
            {
                perror("Errore nella scrittura\n");
                exit(EXIT_FAILURE);
            }     
        } 
    } while (size == BUFFER_SIZE);
    
       

    }else if (S_ISREG(statbuf.st_mode))
    {
    /*è un file, comportamento analogo a quello delle cartelle visto che sono simili*/
    char *path = calloc(PATH_MAX, sizeof(char));
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
    else if (S_ISLNK(statbuf.st_mode))
    {
        /*è un link*/
        int size;
        char buffer2[BUFFER_SIZE];
        if((size = readlink(source, buffer2, BUFFER_SIZE))<0){
            perror("Errore nel link\n");
            exit(EXIT_FAILURE);
        }
    if (synlink(path_destination,buffer2)<0)
    {
       perror("Errore nella creazione del link");
       exit(EXIT_FAILURE);
    }

    }else{
        perror("Tipo non valido\n");
        exit(EXIT_FAILURE);
    }
    
    
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