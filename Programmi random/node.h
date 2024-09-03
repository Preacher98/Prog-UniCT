#ifndef NODE_H
    #define NODE_H
    #include "data.h"
    struct node
    {
        struct dato d;
        struct node *next;
    };
    
#endif