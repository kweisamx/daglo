typedef struct Element{
    int v;
    struct Element *next;
}Element;
void add_edge(int a, int b);
void recursive_delete(Element *e);
void adjancy_lists();
void display(Element *start);
