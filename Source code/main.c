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
    printf("Inserire un intero k maggiore o uguale a 0.\n");
    scanf("%d", &j);
    if (j<0)
        exit(1);
/*Call function to complete request 2, k-core*/
    kcore(G, j, &ok);
    printf("Inserire un intero j maggiore o uguale a 1.\n");
    scanf("%d", &j);
    if (j<1)
        exit(1);
/*Call function to complete request 3, j-edge connected*/
    jedgeconnected(G, j);
    GRAPHfree(G);
    return 0;
}
