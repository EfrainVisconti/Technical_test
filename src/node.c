# include "../inc/even_odd.h"

void free_list(Node *list)
{
    Node *aux;
    while (list != NULL)
    {
        aux = list;
        list = list->next;
        free(aux);
    }
}

Node *get_last_node(Node *list)
{
    if (list == NULL)
    {
        return NULL;
    }

	return (list->last);
}

void    add_new_node(Node **list, int number)
{
    Node *new = malloc(sizeof(Node));
    if (new == NULL)
    {
        fprintf(stderr, "Error: Memory Allocation for a node.\n");
        return ;
    }
    new->number = number;
    new->next = NULL;
    new->last = NULL;
    
    if (*list == NULL)
        *list = new;
    else
    {
        Node *last = get_last_node(*list);
        last->next = new;
    }

    if (new->next == NULL)
        (*list)->last = new;
}