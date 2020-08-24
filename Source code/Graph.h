#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

/*Header file for standard first-class ADT Graph*/

#include "ST.h"

typedef struct {
	int v, w;
} Edge;

typedef struct graph *Graph;

Graph  GRAPHinit(int V);
void   GRAPHfree(Graph G);
Graph  GRAPHload(FILE *fin);
void   GRAPHstore(Graph G, FILE *fout);
int    GRAPHgetIndex(Graph G, char *label);
void   GRAPHinsertE(Graph G, int id1, int id2);
void   GRAPHremoveE(Graph G, int id1, int id2);
void   GRAPHedges(Graph G, Edge *a);
void   GRAPHpath(Graph G, int id1, int id2);
void   GRAPHpathH(Graph G, int id1, int id2);
void   GRAPHdfs(Graph G, int id);
void   GRAPHbfs(Graph G, int id);
int    GRAPHcc(Graph G);
int    GRAPHscc(Graph G);
Graph  GRAPHreverse(Graph G);
void   GRAPHmstK(Graph G);
void   GRAPHmstP(Graph G);
void   GRAPHspD(Graph G, int id);
void   GRAPHspBF(Graph G, int id);

/*Custom internal functions*/
void jedgeconnected(Graph G, int j);
void kcore(Graph G, int k, int *ok);

#endif
