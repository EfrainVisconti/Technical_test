# include "../inc/even_odd.h"

void    free_exit(Program *program)
{
    free(program->threads);
    free_list(program->odd);
    free_list(program->even);
    pthread_mutex_destroy(&(program->even_mutex));
    pthread_mutex_destroy(&(program->odd_mutex));
    exit(EXIT_FAILURE);
}

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
        return (NULL);

	while (list->next != NULL)
		list = list->next;
	return (list);
}

void    add_new_node(Node **list, int number)
{
    Node *new = malloc(sizeof(Node));
    if (new == NULL)
    {
        fprintf(stderr, "Error: malloc().\n");
        return ;
    }
    new->number = number;
    new->next = NULL;

    if (*list == NULL)
        *list = new;
    else
        get_last_node(*list)->next = new;
}