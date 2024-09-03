#include "data.h"

int confronta_dati(struct dato *d1, struct  dato *d2)
{
    if((*d1).value > (*d2).value)
        return 1;
        else if(d1->value < d2->value)
        return -1;
        else return 0;

}
