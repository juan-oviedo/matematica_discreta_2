#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include "EstructuraGrafo23.h"
#include "tad_vertice.h"
#include "int_to_str.h"


#define BUFFSIZE 100

void destroy_solo_hash (char ** lista_de_nombres, u32 size){
    hdestroy();

    for (u32 i = 0; i < size; i++)
    {
        free(lista_de_nombres[i]);
        lista_de_nombres[i] = NULL;
    }
    free (lista_de_nombres);
    lista_de_nombres = NULL;
}

void destroy_list_vertice (vertice * lista, u32 size){

    for (u32 i = 0; i < size; i++)
    {
        vertice_destruir_nodo_con_array(lista[i]);
        lista[i] = NULL;
    }
    free(lista);
    lista = NULL;
}

void merge(vertice * arr, int start, int mid, int end) {
    vertice * temp = malloc((end - start + 1) * sizeof(vertice));
    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end) {
        if (vertice_nombre(arr[i]) <= vertice_nombre(arr[j])) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= end) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (i = start; i <= end; i++) {
        arr[i] = temp[i - start];
    }

    free(temp);
}

void mergeSort(vertice * arr, int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;

        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);

        merge(arr, start, mid, end);
    }
}

void cargar_vertice (vertice *lista, char ** lista_nombres, u32 edge, u32 vecino, unsigned int * vertices_cargados, u32 n){
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
                                                //printf("nombre: %s  vertice: %u\n", entry.key, edge);
        //control para ver que haya la cantidad justa de vertices
        if (*vertices_cargados >= n){
            printf ("hay mas vertices de los aclarados\n");
            //destroy();
            return;
        }

        vertice nodo = vertice_vacio();
        nodo = vertice_init(nodo, edge);
                                                //printf("llego hasta la init\n");
        nodo = vertice_sumar_vecino(nodo, vecino);
        //cargar nodo a la lista
        lista [*vertices_cargados] = nodo;
        lista_nombres [*vertices_cargados] = nombre;

        //cargar nodo a la lista de hash
        //entry.key = nombre;   no es necesaria si arriba ya se hizo
        entry.data = nodo;
        puntero_hash = hsearch(entry, ENTER);

        //cargo la lista de nombres para despues ser liberada

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
        free(nombre);
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
    vertice *lista = calloc(n, sizeof(vertice));
    char ** lista_nombres = calloc (n, sizeof(char *));

    //leemos los lados
    for (u32 i = 0; i < m; i++)
    {
        u32 vertice1;
        u32 vertice2;

        err = fgets(buffer, BUFFSIZE, stdin);
        if (err == NULL)
        {
            printf("Error en la lectura\n");
            //destroy();
            return NULL;
        }
        if (buffer[0] != 'e')
        {
            printf("Error en el formato de los lados\n");
            //destroy();
            return NULL;
        }

        sscanf(buffer, "e %u %u", &vertice1, &vertice2);

                                                    //printf ("vertice 1: %u  vertice 2: %u\n", vertice1, vertice2);

        cargar_vertice(lista, lista_nombres, vertice1, vertice2, &vertices_cargados, n);
        cargar_vertice(lista, lista_nombres, vertice2, vertice1, &vertices_cargados, n);
    }

                                                    //printf ("n de vertices cargados: %u\n", vertices_cargados);
    
    

    //Ordenamos array según orden natural de nombres
    mergeSort(lista, 0, n-1);
    
    //LLenamos campo orden natural
    for (unsigned int i = 0u; i < n; i++){
        lista[i] = vertice_indexar (lista[i], i);
    }
    
    // pasamos de lista ligada de vecinos a array de vecinos
    for (u32 i = 0; i < n; i++)
    {
        lista[i] = vertice_generar_array_adyacencia(lista[i]);
    }
    
    destroy_solo_hash(lista_nombres, n);
                // es para debug
                        int total = 0;
                        for (u32 i = 0; i < n; i++)
                        {
                            total = total + vertice_grado(lista[i]);
                            printf("nodo: %u,  grado: %u indice: %u\n", vertice_nombre(lista[i]), vertice_grado(lista[i]), vertice_indice(lista[i]));
                        }

                                                                        //printf ("grado total: %d\n", total/2);
    




    destroy_list_vertice(lista, n);

    return NULL;
}


int main()
{
    int * a = prueba();
    a = a;
    return 0;
}
