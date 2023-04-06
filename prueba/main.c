#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include "EstructuraGrafo23.h"
#include "tad_vertice.h"
#include "int_to_str.h"

#define BUFFSIZE 100

void destroy (){
    int a = 0;
    a = a;
}

unsigned int cargar_vertice (vertice * lista, u32 edge, u32 vecino, unsigned int vertices_cargados, u32 n){
    ENTRY entry;
    ENTRY * puntero_hash;
    char * nombre = int_to_string(edge);
                                                //printf ("%s\n", nombre);
    entry.key = nombre;
    entry.data = NULL;

    // caso el vertice no esta cargado
    puntero_hash = hsearch(entry, FIND);
    if (puntero_hash == NULL)
    {
                                                printf("nombre: %s  vertice: %u\n", entry.key, edge);
        //control para ver que haya la cantidad justa de vertices
        // if (*vertices_cargados >= n){
        //     printf ("hay mas vertices de los aclarados\n");
        //     destroy();
        //     return;
        // }

        vertice nodo = vertice_vacio();
        nodo = vertice_init(nodo, edge, vertices_cargados);
                                            //printf("llego hasta la init\n");
        nodo = vertice_sumar_vecino(nodo, vecino);
        //cargar nodo a la lista
        lista[vertices_cargados] = nodo;

        //cargar nodo a la lista de hash
        entry.key = nombre;
        entry.data = nodo;
        puntero_hash = hsearch(entry, ENTER);

        vertices_cargados = vertices_cargados + 1;
    }
    else if (vertice_nombre(puntero_hash->data) != edge)
    {
        printf("se le asigno el mismo hash al vertice %u, y al vertice %u! ayuda\n", vertice_nombre(puntero_hash->data), edge);
    }
    //caso en el que el vertice ya esta cargado
    else{
                                            //printf("llego hasta el else\n");
                                            //printf ("%s, %u, %u\n", puntero_hash->key, vertice_nombre(puntero_hash->data), vertice_grado(puntero_hash->data));
        puntero_hash->data = vertice_sumar_vecino(puntero_hash->data, vecino);
    }
    
                                            //printf ("nodo : %u  vecino nuevo: %u  grado: %u\n", vertice_nombre(puntero_hash->data), vecino, vertice_grado(puntero_hash->data));
    puntero_hash = NULL;
    return vertices_cargados;
}

int * prueba (){
    u32 n;
    u32 m;
    unsigned int vertices_cargados = 0;

    char buffer[BUFFSIZE];
    char * err;

    //leemos la primer linea
    err = fgets(buffer, BUFFSIZE, stdin);
                                                //printf ("%s\n",buffer);
    if (err == NULL)
    {
        printf("Error en la lectura\n");
        return NULL;
    }


    //leemos los posibles comentarios
    while (buffer[0] == 'c')
    {
        err = fgets(buffer, BUFFSIZE, stdin);
        if (err == NULL)
        {
            printf("Error en la lectura\n");
            return NULL;
        }
                                                //printf ("%s\n",buffer);
    }
    

    //leemos la cantidad de vertices y lados del grado
    sscanf(buffer, "p edge %u %u", &n, &m);
                                                //printf ("%s\n%u %u\n", buffer, n ,m);
    if (buffer[0] != 'p')
    {
        printf ("Error de formato en la linea que deberia tener 'p edge u32 u32'\n");
        return NULL;
    }
    
    //creamos la hash table con mas espacio para que no haya conflictos
    int error = hcreate(2 * n);
    if (error == 0)
    {
        printf("No se pudo alocar suficiente memoria para la hash table");
        return NULL;
    }

                                                    printf ("vertices: %u, lados: %u\n", n, m);
    vertice lista [n];

    //leemos los lados
    for (u32 i = 0; i < m; i++)
    {
        u32 vertice1;
        u32 vertice2;

        err = fgets(buffer, BUFFSIZE, stdin);
        if (err == NULL)
        {
            printf("Error en la lectura\n");
            destroy();
            return NULL;
        }
        if (buffer[0] != 'e')
        {
            printf("Error en el formato de los lados\n");
            destroy();
            return NULL;
        }

        sscanf(buffer, "e %u %u", &vertice1, &vertice2);

                                                    printf ("vertice 1: %u  vertice 2: %u\n", vertice1, vertice2);

        vertices_cargados = cargar_vertice(lista, vertice1, vertice2, vertices_cargados, n);
        vertices_cargados = cargar_vertice(lista, vertice2, vertice1, vertices_cargados, n);
    }

    for (u32 i = 0; i < n; i++)
    {
        printf("nodo: %u,  grado: %u\n", vertice_nombre(lista[i]), vertice_grado(lista[i]));
    }
    

    return NULL;
}


int main()
{
    int * a = prueba();
    a = a;
    return 0;
}
