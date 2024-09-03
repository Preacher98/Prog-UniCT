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
//Calcolare percorso sorgente e percorso destinazione
void copy(char *source, char *dest){
    
    char path_destination[PATH_MAX];
    strcpy(path_destination, dest);
    strcat(path_destination, "/");
    strcpy(path_destination, basename(source));
    //basename() ti restituisce soltanto il nome del file che è contenuto in un filepath
    //dirname() ti restituisce il percorso che è contentuto in un filepath
    struct stat statbuf;
    if(lstat(source, &statbuf)==-1){ //La funzione lstat usata per seguire il linksimbolico ed ottenere le sue informazioni dato in ingresso, successivamente le informazioni trovate le va ad inserire in una struct di tipo stat. Anche l'orario di creazione

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
       DIR* dp = opendir(source);
       if (dp == NULL){
        perror("Errore nell'apertura della cartella\n");
        exit(EXIT_FAILURE);
       }

       int size;
       char buffer[BUFFER_SIZE];

       struct dirent *entry;
    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name,"..")== 0)
        continue;

        char path_source[PATH_MAX];
        char path_dest[PATH_MAX];

        sscanf(path_source, &statbuf);

        lstat(path_source, &statbuf);
        if (S_ISDIR(statbuf.st_mode))
        {
            sscanf(path_dest, "%s/%s", path_destination, entry->d_name);
            copy_item(path_source, path_dest);
        }else{
            sscanf(path_dest, "%s/%s", path_destination, basename(entry->d_name));
            copy_item(path_source, path_dest);
        }
        
        
    }
    
    
       

    }else if (S_ISREG(statbuf.st_mode))
    {
        /*è un file, comportamento analogo a quello delle cartelle visto che sono simili*/
        int fpint;
        int fpout;

        


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