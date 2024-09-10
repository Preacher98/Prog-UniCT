#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

typedef struct thread_shared_struct
{
    char c;
    unsigned long int occurences[26];
    //int fd_file; ??
}thread_shared;

void *thread_function_al(void *args){
    thread_shared *t_s = (thread_shared *)args;
    
}

void *thread_function_mz(void *args){
    thread_shared *t_s = (thread_shared *)args;
}

int main(int argc, char **argv){
    //Main thread che si occuperà di creare i sotto thread
    thread_shared *S_thread;
    S_thread = (thread_shared *) calloc(1, sizeof(thread_shared));
    pthread_t thread_al,thread_mz;
    //Gestione dell'input
    if (argc < 2 || argc > 2)
    {
       perror("Attenzione inserire file.txt non inserito");
       exit(EXIT_FAILURE);
    }
    char name_text[20];
    strcpy(name_text,argv[1]);

    //Apertura file e salvataggio metadati
    int fd_fileT;
    fd_fileT=open(name_text,O_RDONLY);
    if (fd_fileT == -1)
    {
        perror("Errore nell'apertura del file !\n");
        exit(EXIT_FAILURE);
    }
    //struct già definita che ci permette di immagazzinare i metadati di un determinato file al suo interno
    struct stat fileT;
    if(fstat(fd_fileT, &fileT) == -1){ //La funzione fstat (File stat) ci permette di riempire la struct stat con i metadati del file specificato
        perror("Errore nel controllo dei metadati!\n");
        close(fd_fileT);
        exit(EXIT_FAILURE);
    }
    printf("Dimensione file: %lld\n",(long long) fileT.st_size);
    printf("Proprietario: %d\n", fileT.st_uid);

    //creazione della mappatura del file
    char *addr = mmap(NULL, fileT.st_size, PROT_READ, MAP_SHARED, fd_fileT, 0); //mmap: Funzione che permette di creare una mappatura del file
    if (addr == MAP_FAILED)
    {
        perror("Errore nella creazione della mappa!\n");
        close(fd_fileT);
        exit(EXIT_FAILURE);
    }

    //Creazione dei thread
    pthread_create(&thread_al, NULL, thread_function_al, &S_thread);
    pthread_create(&thread_mz, NULL, thread_function_mz, &S_thread);
    
    //Funzione di unmap ovvero scollegare la mappatura dal file
    if (munmap(addr, fileT.st_size) == -1)
    {
        perror("Unmapping fallito !\n");
        //exit(EXIT_FAILURE);
    }
    
    close(fd_fileT);



}

    /*
    printf("text = %s\n", addr);
    int i = 0;
    do
    {
        if (addr[i] >= 'a' && addr[i] <= 'z')
        {
            S_thread->occurences[addr[i]-'a']++;
        }
        i++;
        
    } while (i <= strlen(addr));
    int c = 65;
    for (int j = 0; j < 26; j++)
    {
        printf("\t%c = %ld\n",c++,S_thread->occurences[j]);
    }
    */