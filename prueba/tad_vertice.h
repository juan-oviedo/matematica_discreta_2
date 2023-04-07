#ifndef _VERTICE_H
#define _VERTICE_H


typedef struct s_vertice_t * vertice;

vertice vertice_vacio ();
vertice vertice_init (vertice v, u32 nombre);
vertice vertice_sumar_vecino (vertice v, u32 vecino);
vertice vertice_indexar (vertice v, u32 indice);
vertice vertice_destruir (vertice v);
u32 vertice_nombre (vertice v);
u32 vertice_grado (vertice v);
u32 vertice_indice (vertice v);
#endif