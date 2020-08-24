#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include <string.h>

struct symboltable {char **a; int maxN; int N;};

/*Initialize data structures for symbol table*/
ST STinit(int maxN) {
  ST st;
  st = malloc(sizeof (*st));
  if (st == NULL)
    exit(1);
  st->a = calloc(maxN, sizeof(char *));
  if (st->a == NULL)
    exit(1);
  st->maxN = maxN;
  st->N = 0;
  return st;
}

/*Free memory previously allocated*/
void STfree(ST st) {
  int i;
  for (i=0; i<st->N; i++)
    if (st->a[i] != NULL)
      free(st->a[i]);
  free(st->a);
  free(st);
}

/*Insert new string in symbol table*/
void STinsert(ST st, char *str) {
  if (st->N+1 >= st->maxN) {
    st->a = realloc(st->a, (2*st->maxN)*sizeof(char *));
    if (st->a == NULL)
      exit(1);
    st->maxN = 2*st->maxN;
  }
  st->a[st->N] = strdup(str);
  st->N++;
}

/*Search by string -> return index*/
int STsearch(ST st, char *str) {
  int i;
  for (i = 0; i  < st->N; i++)
    if (st->a[i]!=NULL && strcmp(str, st->a[i])==0)
      return i;
  return -1;
}

/*Search by index -> return string*/
char *STsearchByIndex(ST st, int i){
  if (i < 0 || i >= st->N)
    return NULL;
  return (st->a[i]);
}

