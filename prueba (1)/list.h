#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>
#include "EstructuraGrafo23.h"

typedef struct s_list_t * list;
typedef u32 list_elem;


list empty_list ();
/* {- Crea una lista vacía. -} */

list addl (list l, list_elem e);
/* {- Agrega el elemento e al comienzo de la lista l. -} */

list destroy_list (list l);
/* {- Libera memoria en caso que sea necesario. -} */

bool is_empty (list l);
/* {- Devuelve True si l es vacía. -} */

list_elem head (list l);
/* {- Devuelve el primer elemento de la lista l -}
{- PRE: not is_empty(l) -} */

list tail (list l);
/* {- Elimina el primer elemento de la lista l -}
{- PRE: not is_empty(l) -}
 */
list addr (list l, list_elem e);
/* {- Agrega el elemento e al final de la lista l. -} */

unsigned int length (list l);
/* {- Devuelve la cantidad de elementos de la lista l -} */

list concat (list l0, list l1);
/* {- Agrega al final de l todos los elementos de l0 en el mismo orden.-} */

list_elem index (list l, unsigned int n);
    /* - Devuelve el n-ésimo elemento de la lista l -
    - PRE: length(l) > n -
    */

list take (list l, unsigned int n);

/* {- Deja en l sólo los primeros n elementos, eliminando el resto -} */

list drop (list l, unsigned int n);
/* {- Elimina los primeros n elementos de l -}
 */
list copy_list (list l);
/* {- Copia todos los elementos de l1 en la nueva lista l2 -} */

void dump_lista (list l);
/* imprime por pantalla los elementos de la lista */

#endif