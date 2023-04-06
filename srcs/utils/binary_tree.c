#include "../../includes/minishell.h"

binarytree	*create_tree(void)
{
	binarytree	*tree;

	tree = calloc(1, sizeof(binarytree));
	if (!tree)
		return (NULL);
	return (tree);
}

static tree_node	*create_new_node(char *data)
{
	tree_node	*new_node;

	new_node = calloc(1, sizeof(tree_node));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	return (new_node);
}

int	insert_data_recursive(tree_node **node, char *data)
{
	int	cmp;

	if (*node == NULL)
	{
		*node = create_new_node(data);
		if (*node == NULL)
			return (-1);
		else
			return (0);
	}
	cmp = strcmp(data, (*node)->data);
	if (cmp < 0)
		return (insert_data_recursive(&(*node)->left, data));
	else if (cmp > 0)
		return (insert_data_recursive(&(*node)->right, data));
	else
		return (-1);
}
