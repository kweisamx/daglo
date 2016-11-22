#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
typedef struct Element{
    int v;
    struct Element *next;
}Element;

int parent = -1;
Element* create(int n)
{
    Element *i = malloc(sizeof(Element));
    i->v = n;
    i-> next = NULL;
    return i;
}

void release(Element *start)
{
    Element *i = start;
    Element *next = NULL;
    for(;i!=NULL;i=next)
    {
        next =i->next;
        free(i);
    }

}
void display(Element *start)
{
    Element *i = start;
    for(;i!=NULL;i=i->next)
       printf("%i -> ",i->v);
    puts("\n\n");
}


void error(char *msg)
{
    fprintf(stderr,"%s:%s\n",msg,strerror(errno));
    exit(1);
}

int main(int argc,char *argv[])
{
    
    FILE *a = fopen("msg.txt","a");
    if(a==NULL)
    {
        puts("Can't write file msg");
        exit(1);
    }
    fprintf(a," i am chlid %s",argv[1]);
    char nenode[6];
    //char *pch;
    sprintf(nenode,"%s\n",argv[2]);
    fprintf(a,", i have these neighbor %s\n",nenode);

   
    fclose(a);
    
    Element *nei_start =NULL;
    Element *nei_i =NULL;
    Element *nei_next = NULL;
    for(int j =0;j<strlen(nenode)-1;nei_i=nei_next)
    {
        int  a= nenode[j]-'0';
 //       printf("nenode = %i\n", a);
        nei_next =create(a);
        if(nei_start==NULL)
            nei_start = nei_next;
        if(nei_i!=NULL)
            nei_i->next =nei_next;
        j++;
    }
    display(nei_start);
    //printf("%s len %d\n",argv[1],(int)strlen(nenode));


}


