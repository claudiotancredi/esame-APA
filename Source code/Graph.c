#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "ST.h"

#define MAXC 11

//funzioni interne standard
static Edge  EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);
static void dfsRcc(Graph G, int v, int id, int *cc);

//funzioni interne non standard, prototipo aggiunto a casa
int comb_sempl(int pos, Edge *val, Edge *vett, int n, int k, int start, int ok, Graph G);
static int *VETTint(int v, int val);

struct graph{
    int V;
    int E;
    int **madj;
    int *vertex;
    int nV;
    ST st;
};

static Edge EDGEcreate(int v, int w) {
  Edge e;
  e.v = v;
  e.w = w;
  return e;
}

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t==NULL)
    exit(1);

  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i]==NULL)
      exit(1);
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

static int *VETTint(int v, int val){ //funzione implementata a casa
    int i;
    int *vett;
    vett=malloc(v*sizeof(int));
    if (vett==NULL)
        exit(1);
    for (i=0; i<v; i++)
        vett[i]=val;
    return vett;
}

Graph GRAPHinit(int V) {
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    exit(1);
  G->V = V;
  G->E = 0;
  G->madj = MATRIXint(V, V, 0);

  G->vertex=VETTint(V, 1); //aggiunto a casa
  G->nV=V;                 //aggiunto a casa

  G->st = STinit(V);
  return G;
}

void GRAPHfree(Graph G) {
  int i;
  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);

  free(G->vertex); //aggiunto a casa

  STfree(G->st);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(G->st, label1);
  }

  while(fscanf(fin, "%s %s", label1, label2) == 2) {
    id1 = STsearch(G->st, label1);
    id2 = STsearch(G->st, label2);
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2);
  }
  return G;
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = 1;
  G->madj[w][v] = 1;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
  insertE(G, EDGEcreate(id1, id2));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2));
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->madj[v][w] == 1)
    G->E--;
  G->madj[v][w] = 0;
  G->madj[w][v] = 0;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=v+1; w < G->V; w++)
      if (G->madj[v][w] == 1)
        a[E++] = EDGEcreate(v, w);
}

void jedgeconnected(Graph G, int j){
    int i, cc=1, ok=1, k;
    Edge *vett, *val;
    val=(Edge*)malloc(G->E*sizeof(Edge));
    if (val==NULL)
        exit(1);
    GRAPHedges(G, val);
    for (i=1; i<=G->E && cc==1; i++){  //dovevo controllare che ALMENO j archi lo sconnettessero
            //ho cambiato il valore di fine ciclo
        vett=(Edge*)malloc(i*sizeof(Edge));
        if (vett==NULL)
            exit(1);
        cc=comb_sempl(0, val, vett, G->E, i, 0, ok, G); //ho riordinato un po' i parametri
        if (cc==0 && i<j)
            printf("Esiste un insieme di archi di cardinalità < j che sconnette il grafo. "
                   "Grafo non j-edge-connected.\n");
        else if (cc==0 && i>=j){ //ho cambiato la condizione, i>=j
            printf("Grafo j-edge-connected. Archi che lo sconnettono:\n");
            for (k=0; k<i; k++){
                printf("(%s, %s)\n", STsearchByIndex(G->st, vett[k].v), STsearchByIndex(G->st, vett[k].w));
            }
        }
        free(vett);
    }
    free(val); //aggiunto a casa
    return;
}

int comb_sempl(int pos, Edge *val, Edge *vett, int n, int k, int start, int ok, Graph G){
    //ho riordinato i parametri passati alla funzione
    int i, cc;
    if (pos>=k){
        for(i=0; i<k; i++){
            GRAPHremoveE(G, vett[i].v, vett[i].w);
        }
        cc=GRAPHcc(G);
        if (cc!=1)
            ok=0;
        for (i=0; i<k; i++){
            GRAPHinsertE(G, vett[i].v, vett[i].w);
        }
        return ok;
    }
    for (i=start; i<n; i++){
        vett[pos]=val[i];
        if (comb_sempl(pos+1, val, vett, n, k, i+1, ok, G)==0)
            return 0;
    }
    return ok;
}

int GRAPHcc(Graph G) {
  int v, id = 0, *cc;
  cc = malloc(G->V * sizeof(int));
  if (cc == NULL)
    exit(1);

  for (v = 0; v < G->V; v++)
    cc[v] = -1;

  for (v = 0; v < G->V; v++)
    if (cc[v] == -1)
      dfsRcc(G, v, id++, cc);
      //ho tolto la stampa che non mi serve
  return id;
}

static void dfsRcc(Graph G, int v, int id, int *cc) {
  int i;
  cc[v] = id;
  for (i=0; i<G->V; i++){
    if (G->madj[v][i]==1){
        if (cc[i]==-1)
            dfsRcc(G, i, id, cc);
    }
  }
}

void kcore(Graph G, int k, int *ok){
    //nel compito ho dimenticato l'asterisco ad ok ma era chiaramente passato by reference
    int i, j, degree;
    int *v=calloc(G->V,sizeof(int)); //ho aggiunto questo vettore per segnarmi gli archi
    //che tolgo, che poi devo riaggiungerli
    //posso inizializzarlo all'inizio (e non ad ogni iterazione)
    //perché lo uso una sola volta per poi ricorrere,
    //non lo riutilizzo più in una certa istanza della funzione
    if (v==NULL)
        exit(1);
    for (i=0; i<G->V; i++){
        degree=0;
        if (G->vertex[i]==1){
            for (j=0; j<G->V; j++){
                if (G->madj[i][j]==1){
                    degree++;
                }
            }
            if (degree<k){
                G->vertex[i]=0;
                for (j=0; j<G->V; j++){
                    if (G->madj[i][j]==1){
                        GRAPHremoveE(G, i, j);
                        v[j]=1; //segno che ho tolto l'arco con j come estremo destro, aggiunto a casa
                    }
                }
                G->nV--;
                kcore(G, k, ok);
                if (*ok==1){
                    //in fase di chiusura ricorsiva devo ripristinare le condizioni iniziali del grafo!
                    G->vertex[i]=1; //resetto il vertice
                    G->nV++; //incremento il parametro
                    for (j=0; j<G->V; j++){
                        if (v[j]==1){ //se l'arco (i, j) era stato rimosso
                            GRAPHinsertE(G, i, j); //lo reinserisco
                        }
                    }
                    free(v); //libero il vettore prima di fare return
                    return;
                }
            }
        }
    }
    *ok=1;
    //le stampe le ho aggiunte a casa
    if (G->nV==0){
        printf("Non ci sono vertici che formano il k-core!\n");
    }
    else{
        printf("Vertici del k-core:\n");
        for (i=0; i<G->V; i++){
            if (G->vertex[i]==1){
                printf("%s\n", STsearchByIndex(G->st, i));
            }
        }
    }
    free(v); //libero anche qui il vettore per evitare memory leak
    return;
}
