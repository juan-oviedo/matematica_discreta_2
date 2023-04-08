#ifndef _LIST_H
#define _LIST_H

#include "EstructuraGrafo23.h"

typedef struct s_list_t * list;
typedef u32 list_elem;


list empty_list ();
/* {- Crea una lista vacía. -} */

list addl (list l, list_elem e);
/* {- Agrega el elemento e al comienzo de la lista l. -} */

list destroy_list (list l);
/* {- Libera memoria en caso que sea necesario. -} */

list_elem head (list l);
/* {- Devuelve el primer elemento de la lista l -}
{- PRE: not is_empty(l) -} */

list tail (list l);
/* {- Elimina el primer elemento de la lista l -}
{- PRE: not is_empty(l) -}
 */

unsigned int length (list l);
/* {- Devuelve la cantidad de elementos de la lista l -} */

#endif