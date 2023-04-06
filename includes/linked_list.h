#ifndef LINKED_LIST_H
# define LINKED_LIST_H

typedef struct node {
	char		*data;
	struct node	*next;
} node;

typedef struct list {
	node	*headnode;
} list;

list	*create_linkedlist(void);
node	*create_new_node(char *data);
int		get_the_index_of_the_string(list *linked_list, char *to_find);
node	*get_node_by_the_index(list *linked_list, int index);
int		insert_data_to_the_index(list *linked_list, int index, char *data);
int		add_data(list *linked_list, char *data);
int		remove_node(list *linked_list, int index);
void	display_list(list *linked_list);
void	destroy_list(list **linked_list);

#endif