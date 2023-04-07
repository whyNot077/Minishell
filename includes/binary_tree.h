#ifndef BINARY_TREE_H
# define BINARY_TREE_H
# include "structure.h"

binarytree	*create_tree(void);
int			remove_data_recursive(binarytree *tree, char *data);
int			remove_node(tree_node **node, char *data);
void		inorder(binarytree *tree);
void		preorder(binarytree *tree);
void		postorder(binarytree *tree);
void		levelorder(binarytree *tree);
void		display_tree(binarytree *tree);
void		destroy_tree(binarytree **tree);

#endif