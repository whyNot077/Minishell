#ifndef DATA_STRUCTURE_H
# define DATA_STRUCTURE_H

// dynamic array
t_array		*create_list(size_t max_num);
t_token		*get_token(t_array *list, size_t index);
int			is_full(t_array *list);
int			insert_token(t_array *list, char *value);
void		display_list(t_array *list);
void		destroy_list(t_array **list);

// binary tree
binarytree	*create_tree(void);
tree_node	*create_new_node(t_token *token);
void		destroy_tree(binarytree **tree);
void		free_tree_nodes(tree_node *node);

// display
void		display_tree(tree_node *node);

#endif