#ifndef _GRAFO_H
#define _GRAFO_H
#define max_u32 4294967295

typedef unsigned int u32;

#include "EstructuraGrafo23.h"
#include "tad_vertice.h"
#include "int_to_str.h"

typedef struct{
	u32 n;
	u32 m;
	u32 delta;
	vertice * vertice;
}GrafoSt;

typedef GrafoSt *Grafo;

Grafo ConstruirGrafo();
void DestruirGrafo(Grafo G);
u32 NumeroDeVertices(Grafo G);
u32 NumeroDeLados(Grafo G);
u32 Delta(Grafo G);
u32 Nombre(u32 i,Grafo G);
u32 Grado(u32 i,Grafo G);
u32 IndiceVecino(u32 j,u32 i,Grafo G);


#endif