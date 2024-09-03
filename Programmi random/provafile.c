#include <stdio.h> 
#include <stdlib.h> 

int main(){

    const char *filename = "output_fputs.txt"; //Nome del file, Usa .txt perchè immetteremo dati di tipo ben definito
    const char *mode = "w"; //Modalità nel quale decide di aprire il file, in questo caso è in modalità Write(Scrittura)
    char s[50]; //Stringa di 50 caratteri che andremo a metere nel nostro file

    FILE *fp = fopen(filename, mode); // generazione di un puntatore di tipo FILE chimato fp e generazione del file
    if(!fp){
	fprintf(stderr, "\n Error opening file %s with mode %s", filename, mode); 
	perror(""); 
    }

    printf("\n Opened file %s for writing..", filename); 


    int onemore=1;//controllore per l'uscita dal while
    int nw=0;

	do{
	    printf("\n Inserisci una linea di testo (max 50 caratteri) oppure CTRL-d/CTRL-z: "); 

	    if(fgets(s, 50, stdin)==NULL){
		fprintf(stderr, "\n Error reading text from stdin, possibly EOF..");
		onemore=0;
	    }

	    else {
		if(fputs(s,  fp)==EOF){
		    fprintf(stderr, "\n Error writing on file %s", filename);
		    onemore=0;
		}
		else
		    nw++; 
	    }
	}while(onemore && !feof(fp));	

	// chiude il file 
	if(fclose(fp)==EOF) // implica in ogni caso una invocazione della funzione fflush()..
	    perror("\n Error closing file ..");
	else
	    printf("\n File %s closed, %d lines written\n", filename, nw); 

    mode="r";
    fp=fopen(filename,mode);
    
    while (!feof(fp))
    {
      if(fscanf(fp,"%s",s)!=EOF)
        printf("%s \n",s);
    else
        break;
    };
    fclose(fp);
	return 0;
    }
