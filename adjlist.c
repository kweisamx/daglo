#include"adjlist.h"
#include<stdio.h>
#include<stdlib.h>
/*
typedef struct Element{
    int v;
    struct Element *next;
}Element;
*/

Element* create(int n);
Element *list[6];

void add_edge(int a, int b)
{
    Element *e = NULL;
    e =create(b);//e is a pointer point to Element
    e->next = list[a];//let e next point to the inital point of a
    list[a] = e;
}
void recursive_delete(Element *e)
{
    if(!e) return;
    recursive_delete(e->next);
    free(e);

}
void adjancy_lists()
{
    for(int i =0;i<6;i++)
    {
        recursive_delete(list[i]);
        list[i] = 0;
    }
    int a ,b ;
    while(scanf("%i %i",&a,&b)!=EOF)
        add_edge(a,b);
}

void display(Element *start)
{
    Element *i = start;
    for(;i!=NULL;i=i->next)
        printf(" %d link ",i->v);
    puts("\n\n");
}

