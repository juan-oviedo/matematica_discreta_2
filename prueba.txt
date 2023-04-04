grafo {
    n_vertice int
    n_lados int
    delta int
    array * array_ordenado [n]
}

typedef struct entry {
               char key (seria el id);
               voiddata puntero a estructura vertice;
           } ENTRY;

vertice{
    id int (creo q no hace falta)
    grado int
    orden natural int
    lista ligada vecinos (aca guardamos el hash o el id) puntero al inicio del de la lista enlazada
}

listaligada{
    id int
    next * listaligada
}


vertice * array_ordenado [n]

u32 buscar_vecino

u32 IndiceVecino(u32 j,u32 i,Grafo G){
    vertice v = array_ordenado [i];
    .
    .
    .
    algunos controles
    .
    .
    .
    int vecino;
    a = 0;

    lista * aux
    aux = v.listaligada

    while (a < j)
    {
        aux = aux.next
        a ++
    }

    vecino = aux.id
    
    resultado = search (vecino).data.orden_natural
}

1)
11 513

2)cargar el 11 y actualizar la lista con el 513

3) lo mismo con el 513



1)
11 513

2) pasar de id 11 a hash (puntero), si esta en null, guardar memoria para la estructura vertice

3)cargar el 11 y actualizar la lista con el 513

5) lo mismo con el 513

.
.
.

cuando ya esta todo el grafo cargado:

1) ordenamos lo de la tabla (array_ordenado [0] = arreglodehash [hash(de 5)].data) de hash en un arreglo y completamos el campo orden natural de cada vertice

por ej: entramos a la lista de adyacencia del indice 0 y queremos ver el indice del orden natural del vecino 6
para encontrar el orden natural de un vecino, calculamos el hash de 5, entramos al data.orden natural