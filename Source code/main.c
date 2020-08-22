#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char *argv[]){
    FILE *fp;
    fp=fopen(argv[1], "r");
    if (fp==NULL)
        exit(1);
    Graph G;
    int j, ok=0;
    G=GRAPHload(fp);
    fclose(fp);
    //ho riordinato il main chiamando prima la funzione per il punto 2 e poi quella per il punto 3
    printf("Inserire un intero k maggiore o uguale a 0.\n");
    scanf("%d", &j);
    if (j<0)
        exit(1); //controllo aggiunto a casa
    kcore(G, j, &ok);
    printf("Inserire un intero j maggiore o uguale a 1.\n");
    scanf("%d", &j);
    if (j<1)
        exit(1); //controllo aggiunto a casa
    jedgeconnected(G, j);
    GRAPHfree(G); //aggiunta a casa
    return 0;
}
