#include <assert.h>
#include <stdlib.h>


#include "EstructuraGrafo23.h"
#include "list.h"
#include "tad_vertice.h"

struct s_vertice_t {
    u32 nombre;
    u32 grado;
    unsigned int indice_provisorio;
    u32 indice;
    list vecinos;
};

vertice vertice_vacio (){
    vertice v = NULL;
    return v;
}

vertice vertice_init (vertice v, u32 nombre, unsigned int indice_provisorio){
    assert(v == NULL);

    v = malloc(sizeof (struct s_vertice_t));
    v->nombre = nombre;
    v->grado = 0;
    v->indice_provisorio = indice_provisorio;
    v->indice = 4294967295;
    v->vecinos = empty_list();

    return v;
}

vertice vertice_sumar_vecino (vertice v, u32 vecino){
    assert (v != NULL);

    v->vecinos = addl(v->vecinos, vecino);

    v->grado = v->grado + 1;
    return v;
}

vertice vertice_indexar (vertice v, u32 indice){
    assert (v->indice == 4294967295);
    v->indice = indice;

    return v;
}

u32 vertice_nombre (vertice v){
    return v->nombre;
}

u32 vertice_grado (vertice v){
    return v->grado;
}

vertice vertice_destruir (vertice v){
    assert (v != NULL);
    v->vecinos = destroy_list (v->vecinos);
    free (v);
    v = NULL;

    return v;
}
