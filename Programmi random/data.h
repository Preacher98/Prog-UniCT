#ifndef DATA_H //Direttive preprocessore
    #define DATA_H
    struct dato{
        int value;
    };

    int confronta_dati(struct dato *d1, struct  dato *d2);
       /*Restituisce 0 se i dati sono uguali oppure -1 se (*d1.value < *d2.value )  oppure 1 se (*d1.value > *d2.value)*/
    
#endif