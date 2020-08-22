#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED

typedef struct symboltable *ST;

ST    STinit(int maxN);
int   STcount(ST st);
void  STinsert(ST st, char *label);
int  STsearch(ST st, char* k);
char*  STsearchByIndex(ST st, int i);
void  STdelete(ST st, char* k);
char*  STselect(ST st, int r);
void  STdisplay(ST st);
int   STempty(ST st);
void  STfree(ST st);

#endif
