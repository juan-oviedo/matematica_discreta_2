#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include "EstructuraGrafo23.h"
#include "tad_vertice.h"
#include "int_to_str.h"
#include "list.h"

#define BUFFSIZE 100

// falta destroy / ordenar la lista / lista de adyacencia / funciones del grafo y vertices / sacar asserts y limpiar codigo

void destroy (){
    //como sabemos cuantos elementos destruir, si usamos destroy en cualquier 
    //parte de la carga, y tenemos memoria dinámica pedida para las keys
}

int vertex_compare(const void *v1, const void  *v2){
    int result = 0;
    if (vertice_nombre(v1)<vertice_nombre(v2)){
        result = -1;
    }else if (vertice_nombre(v1)>vertice_nombre(v2)){
        result = 1;
    }
    return result;
}

void cargar_vertice (vertice * lista, u32 edge, u32 vecino, unsigned int * vertices_cargados, u32 n){
    ENTRY entry;
    ENTRY * puntero_hash;
    char * nombre = int_to_string(edge);
                                                printf ("%s\n", nombre);
    entry.key = nombre;
    entry.data = NULL;

    // caso el vertice no esta cargado
    puntero_hash = hsearch(entry, FIND);
    if (puntero_hash == NULL)
    {
                                                //printf("nombre: %s  vertice: %u\n", entry.key, edge);
        //control para ver que haya la cantidad justa de vertices
        if (*vertices_cargados >= n){
            printf ("hay mas vertices de los aclarados\n");
            destroy();
            return;
        }

        vertice nodo = vertice_vacio();
        nodo = vertice_init(nodo, edge);
                                                //printf("llego hasta la init\n");
        nodo = vertice_sumar_vecino(nodo, vecino);
        //cargar nodo a la lista
        lista[*vertices_cargados] = nodo;

        //cargar nodo a la lista de hash
        //entry.key = nombre;   no es necesaria si arriba ya se hizo
        entry.data = nodo;
        puntero_hash = hsearch(entry, ENTER);

        *vertices_cargados = *vertices_cargados + 1;
    }

    else if (vertice_nombre(puntero_hash->data) != edge)
    {
                    // NO DEBERIA ENTRAR!
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

                                                //printf ("vertices: %u, lados: %u\n", n, m);
    vertice lista[n];

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

                                                    //printf ("vertice 1: %u  vertice 2: %u\n", vertice1, vertice2);

        cargar_vertice(lista, vertice1, vertice2, &vertices_cargados, n);
        cargar_vertice(lista, vertice2, vertice1, &vertices_cargados, n);
    }

                                                    //printf ("n de vertices cargados: %u\n", vertices_cargados);
    //Ordenamos array según orden natural de nombres
    qsort(lista, n, sizeof(vertice), vertex_compare);
    //LLenamos campo orden natural
    for (unsigned int i = 0u; i<n; i++){
        //necesitamos acceso a la estructura desde este file, para acceder al campo?
        lista[i]->indice = i;
    }
    //PASAJE DE LISTA DE ADYACENCIA A ARRAY DE ADYACENCIA
    unsigned int list_size;
    vertice current, vecino;
    ENTRY entry, *ep;

    //iteramos sobre todos los vértices del array
    for (unsigned int i = 0u; i<m; i++){
        current = lista[i];
        list_size = vertice_list_size(current);
        current->arr_vecinos = malloc(list_size*sizeof(u32));
        //iteramos sobre todos los vecinos del vértice i
        for (unsigned int j = 0u; j<list_size; j++){
            entry.key = int_to_string(head(current->vecinos));
            current->vecinos = tail(current->vecinos);
            ep = hsearch(entry, FIND);
            //Chequeamos posible error, si funciona podemos eliminarlo
            if (ep == NULL){
                printf("error en encontrar vecino desde la hash table\n");
                destroy();
                exit(EXIT_FAILURE);
            }
            vecino = ep->data;
            current->arr_vecinos[j] = vecino->indice;
        }
        //ya no necesitamos la linked list de adyacencia
        current->vecinos = destroy(current->vecinos);
    }

    


                // es para debug
                        int total = 0;
                        for (u32 i = 0; i < n; i++)
                        {
                            total = total + vertice_grado(lista[i]);
                            printf("nodo: %u,  grado: %u\n", vertice_nombre(lista[i]), vertice_grado(lista[i]));
                        }

                                                                        //printf ("grado total: %d\n", total/2);
    

    return NULL;
}


int main()
{
    int * a = prueba();
    a = a;
    return 0;
}
