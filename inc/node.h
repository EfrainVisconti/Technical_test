#ifndef NODE_H
# define NODE_H

typedef struct Node
{
	int	number;
	struct Node *next;
} Node;

//node.c
void free_list(Node *list);
Node  *get_last_node(Node *list);
void    add_new_node(Node **list, int number);

#endif