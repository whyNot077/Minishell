#include "../../includes/minishell.h"

static void	remove_leaf_node(tree_node **node)
{
	free((*node)->data);
	free(*node);
	*node = NULL;
}

static void	remove_node_with_right_child(tree_node **node)
{
	tree_node	*temp;

	temp = *node;
	*node = (*node)->right;
	free(temp->data);
	free(temp);
}

static void	remove_node_with_left_child(tree_node **node)
{
	tree_node	*temp;

	temp = *node;
	*node = (*node)->left;
	free(temp->data);
	free(temp);
}

static void	remove_node_with_two_children(tree_node **node)
{
	tree_node	*min_node;

	min_node = (*node)->right;
	while (min_node->left != NULL)
		min_node = min_node->left;
	free((*node)->data);
	(*node)->data = strdup(min_node->data);
	remove_node(&(*node)->right, min_node->data);
}

int	remove_node(tree_node **node, char *data)
{
	int	cmp;

	if (*node == NULL)
		return (-1);
	cmp = strcmp(data, (*node)->data);
	if (cmp < 0)
		return (remove_node(&(*node)->left, data));
	else if (cmp > 0)
		return (remove_node(&(*node)->right, data));
	else
	{
		if ((*node)->left == NULL && (*node)->right == NULL)
			remove_leaf_node(node);
		else if ((*node)->left == NULL)
			remove_node_with_right_child(node);
		else if ((*node)->right == NULL)
			remove_node_with_left_child(node);
		else
			remove_node_with_two_children(node);
	}
	return (0);
}

int	remove_data_recursive(binarytree *tree, char *data)
{
	if (tree == NULL || tree->root == NULL)
		return (-1);
	return (remove_node(&tree->root, data));
}
