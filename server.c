#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
typedef struct Element{
    int v;
    struct Element *next;
}Element;

Element *list[6];

Element* create(int n)
{
    Element *i = malloc(sizeof(Element));
    i->v = n;
    i-> next = NULL;
    return i;
}

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
        printf("%d",i->v);
    puts("\n\n");
}
void whoneighbor(Element *start, char *neigh)
{
    Element *i = start;
    for(;i!=NULL;i=i->next)
    {
        *neigh=i->v+'0';
        neigh++;
    }
}

void error(char *msg)
{
    fprintf(stderr,"%s:%s\n",msg,strerror(errno));
    exit(1);
}





/*create 6 process run algo */
int main()
{   
    int fdcs[6][2];//pipe client to server
   // int fdsc[6][2];//pipe server to client
    for(int i = 0;i<6;i++)
    {
        if(pipe(fdcs[i])==-1)
            error("Can't create pipe");
    }

    int a,b;
    while(scanf("%i %i",&a,&b)!=EOF)
    {
       // printf("%i %i\n",a,b);
        add_edge(a,b);
        add_edge(b,a);
    }
 /*   for(int i = 0;i<6;i++)
    {
        printf("%i ",i);
        display(list[i]);
    }
  */ 
    for(int i =0; i < 6;i++)
    {
        pid_t pid = fork();
        if(pid==-1){
            error("Can't fork process");
        }
        if(!pid){//child
            //dup2(fdcs[i][1],1);//let stdout to server stdin
            //close(fdcs[i][0]);
            char neighbor[5];
           // puts("====================");
            whoneighbor(list[i],neighbor);
           // printf(" %i the neighborhood %s\n",i,neighbor);
           // puts("=====================");
            char clientnu[20];

            sprintf(clientnu,"%i",i);
            char *var[] = {clientnu,neighbor,NULL};
            if(execl("./client","./client",var[0],var[1],NULL)==-1){
                error("Can't exec process");     
            }
        
        }
        //dup2(fdcs[i][0],0);
        //close(fdcs[i][1]);
    }
    sleep(2);
    char msg[80];
    FILE *messg =fopen("msg.txt","r");
    while(fgets(msg,80,messg))
    {
        printf("%s\n",msg);     
    
    }
    fclose(messg);
    system("rm msg.txt");
    
    return 0; 
}
