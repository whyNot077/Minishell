/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:13:17 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 14:11:32 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

binarytree	*create_tree(void)
{
	binarytree	*tree;

	tree = 	ft_calloc(1, sizeof(binarytree));
	if (!tree)
		return (NULL);
	return (tree);
}

tree_node	*create_new_node(t_token *token)
{
	tree_node	*new_node;

	new_node = 	ft_calloc(1, sizeof(tree_node));
	if (!new_node)
		return (NULL);
    new_node->data = token->value;
    new_node->type = token->type;
    new_node->left = NULL;
    new_node->right = NULL;
	return (new_node);
}

static void	free_tree_nodes(tree_node *node)
{
	if (!node)
		return ;
	free_tree_nodes(node->left);
	free_tree_nodes(node->right);
	free(node->data);
	free(node);
}

void	destroy_tree(binarytree **tree)
{
	if (!tree || !*tree)
		return ;
	free_tree_nodes((*tree)->root);
	free(*tree);
	*tree = NULL;
}
