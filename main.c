#include <stdlib.h>
#include "EstructuraGrafo23.h"

int main()
{
    Grafo G = NULL;
    G = ConstruirGrafo();
    DestruirGrafo(G);
    return 0;
}
