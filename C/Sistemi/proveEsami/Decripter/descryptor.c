#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
//Questo è stato il primo tentativo, sono reduce dall'esperienza. Cose capite:
// 1) Capire cosa i thread condividono e cosa invece hanno di privato
// 2) snellire il main, utilizzare funzioni e capire cosa passare ad esse e cosa invece no
// 3) Niente variabili globali, già non lo facevo però è giusto ricordarlo
typedef struct file
{
    char file_key[100];
    char file_text[100];
}file_decrpt;

typedef struct buffer
{
  char buff[1000];
  int dim;
}bufferT;

typedef struct buffer2
{
  char buffe[27];
  int dim;
}bufferK;

typedef struct thread_param
{
  bufferT str_text;
  bufferK str_keys;
  int fd_keys;
  int fd_text;
}threadArg;


int lettura_Text(int fd_text, bufferT *temp_text, int bytes){
  
  char c=' ';
  int i=0, bytes_read=0;
  char temp[1];
  while ((bytes_read=read(fd_text, temp, 1))>0)
  {
    if (temp[0] == '\n')
    {
      
      break;
    }
    temp_text->buff[i++]=temp[0];
    if (i > strlen(temp_text->buff))
    {
      perror("Errore overflow");
      break;
    }
    
  }
  temp_text->buff[i]='\0';
  if (bytes_read <= 0)
  {
    perror("Errore nella lettura dei bytes!!\n");
    return 1;
  }
  lseek(fd_text, bytes+bytes_read-1, SEEK_CUR);
  temp_text->dim=strlen(temp_text->buff);
  return bytes_read;
}

int lettura_Key(int fd_keys, int bytes, threadArg *str_thread, int num_key){
  char c=' ';
  int i=0, bytes_read=0, t=0;
  char temp[1];
  while ((bytes_read=read(str_thread->fd_keys, temp, 1))>0)
  {
    if (temp[0] == '\n')
    { 
      t++;
      i=-1;
      if (t >= num_key)
      {
        break;
      }
    }
    
    str_thread->str_keys.buffe[i++]=temp[0];
    //printf("%d\n",i);
    if (i >= str_thread->str_keys.dim )
    {
      perror("Errore overflow");
      break;
    }
    
  }

  str_thread->str_keys.buffe[i]='\0';
  if (bytes_read <= 0)
  {
    perror("Errore nella lettura dei bytes!!\n");
    return 1;
  }
  
  lseek(fd_keys, bytes+bytes_read-1, SEEK_CUR);
  return bytes_read;
}

char convert_char(threadArg *str_thread, char c){
  char t;
  
  if (c == ' '){
        return c;
      }

    for (int i = 0; i < str_thread->str_keys.dim ; i++)
    {
      
      
      t=tolower(str_thread->str_keys.buffe[i]);
      if (t == c)
      {
        return (char) 65+i;
      }
      
    }
    
    return c;

}

void decrypter(threadArg *str_thread){
  for (int i = 2; i < strlen(str_thread->str_text.buff); i++)
  {
    //printf("Carattere attuale: %c\n", temp_text->buff[i]);
    str_thread->str_text.buff[i] = convert_char(str_thread, str_thread->str_text.buff[i]);
    //printf("Carattere convertito: %c\n", temp_text->buff[i]);
  } 
}

void *thread_function1(void *argument){
  threadArg *str_thread = (threadArg *) argument;
  printf("Sono il thread 1 sto codificando\n");
  lettura_Key(str_thread->fd_keys,0,str_thread,1);
  printf("%s\n",str_thread->str_keys.buffe);
  decrypter(str_thread);
  printf("%s\n",str_thread->str_text.buff);
  return NULL;
}
void *thread_function2(void *argument){
  threadArg *str_thread = (threadArg *) argument;
  printf("Sono il thread 2 sto codificando\n");
  lettura_Key(str_thread->fd_keys,0,str_thread,2);
  printf("%s\n",str_thread->str_keys.buffe);
  decrypter(str_thread);
  printf("%s\n",str_thread->str_text.buff);
  return NULL;
}
void *thread_function3(void *argument){
  threadArg *str_thread = (threadArg *) argument;
  printf("\nSono il thread 3 sto codificando\n");
  lettura_Key(str_thread->fd_keys,0,str_thread,3);
  printf("%s\n",str_thread->str_keys.buffe);
  decrypter(str_thread);
  printf("%s\n",str_thread->str_text.buff);
  return NULL;
}



int main(int argc, char **argv){
  if (argc <3)
  {
    perror("Errore nell'inserimento dei valori !");
    return 1;
  }
  //Dichiarazione delle variabili
  //bufferT temp_text;
  //bufferK temp_keys;
  //temp_text.dim=1000;
  //temp_keys.dim=27;
  threadArg *argumentT = (threadArg*)calloc(1, sizeof(threadArg));
  file_decrpt dec;

  strcpy(dec.file_key,argv[1]);
  printf("%s\n",dec.file_key);
  strcpy(dec.file_text,argv[2]); 
  printf("%s\n",dec.file_text);

  argumentT->fd_keys = open(dec.file_key, O_RDONLY);
  argumentT->fd_text = open(dec.file_text, O_RDONLY);
  int num_key=0;
  int bytes_read_T=0;
  int bytes_read_K=0;

  pthread_t vet_thread[3];

  for(int j=0; j<3;j++)
  {
  memset(argumentT->str_text.buff, 0, sizeof(argumentT->str_text.buff));
  bytes_read_T = lettura_Text(argumentT->fd_text, &argumentT->str_text, bytes_read_T); 
  num_key = argumentT->str_text.buff[0] - '0';
  //num_key = atoi(&argumentT.str_text.buff[0]);
  printf("%s, %d",argumentT->str_text.buff, num_key);

  switch (num_key)
  {
  case 1:
    if (pthread_create(&vet_thread[0], NULL,thread_function1, &argumentT) != 0)
    {
      perror("Errore nella creazione del thread!\n");
      return 1;
    }
    break;
  case 2:
    if(pthread_create(&vet_thread[1], NULL,thread_function2, &argumentT) != 0){
      perror("Errore nella creazione del thread!\n");
      return 1;
    }
    break;
  case 3:
    if (pthread_create(&vet_thread[2],NULL, thread_function3, &argumentT) != 0)
    {
      perror("Errore nella creazione del thread!\n");
      return 1;
    }
    
    break;
  
  default:
    break;
  } 
  if(bytes_read_K == -1)
  {
    perror("Errore nella lettura del file!\n");
    return -1;
  }
pthread_join(vet_thread[0],NULL);
pthread_join(vet_thread[1],NULL);
pthread_join(vet_thread[2],NULL);
}
  close(argumentT->fd_keys);
  close(argumentT->fd_text);
}
  //Funzioni
  /*
  
  //printf("%s\n",temp_text.buff);
  lettura_Text(fd_text, &temp_text, bytes_read_T);
  printf("%s\n",temp_text.buff);
  //lettura_Text(fd_text, &temp_text, bytes_read_T);
  //printf("%s\n",temp_text.buff);
  
  printf("%d\n", num_key);
  bytes_read_K = lettura_Key(fd_keys, bytes_read_K, &temp_keys, num_key);
  printf("%s\n",temp_keys.buffe);

  //printf("%s\n",temp_text.buff);
  decrypter(&temp_text, &temp_keys);
  printf("%s",temp_text.buff);
  */
