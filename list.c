#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct s_list_t {
    list_elem elem;
    list next;
};

list empty_list (){
    list l = NULL;
    return l;
}

list addl (list l, list_elem e){
    list p = NULL;
    p = malloc(sizeof(struct s_list_t));
    
    p->elem = e;
    p->next = l;
    l = p;
    
    return l;
}

list destroy_list (list l){
    list p;

    while ( l != NULL){
        p = l;
        l = l->next;
        p->next = NULL;
        free (p);
    }

    return l;
}


list_elem head (list l){

    list_elem e;

    e = l->elem;

    return e;
}

list tail (list l){
    list p;
    p = l;
    l = l->next;
    p->next = NULL;
    free (p);
    
    return l;
}

unsigned int length (list l){
    unsigned int n = 0;
    list p;
    
    p = l;
    while (p != NULL){
        n ++;
        p = p->next; 
    }

    return n;
}