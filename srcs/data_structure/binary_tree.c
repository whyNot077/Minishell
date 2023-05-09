/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:13:17 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/09 18:44:43 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_binarytree	*create_tree(void)
{
	t_binarytree	*tree;

	tree = 	ft_calloc(1, sizeof(t_binarytree));
	if (!tree)
		return (NULL);
	return (tree);
}

t_tree_node	*create_new_node(char *value, int type)
{
	t_tree_node	*new_node;

	new_node = 	ft_calloc(1, sizeof(t_tree_node));
	if (!new_node)
		return (NULL);
    new_node->value = value;
    new_node->type = type;
	return (new_node);
}

void	free_tree_nodes(t_tree_node *node)
{
	if (!node)
		return ;
	free_tree_nodes(node->left);
	if (node->type == HEREDOC)
	{
		unlink(node->filename);
		free(node->filename);
	}
	free_tree_nodes(node->right);
	free(node->command);
	free(node);
}

void	destroy_tree(t_binarytree **tree)
{
	if (!tree || !*tree)
		return ;
	free_tree_nodes((*tree)->root);
	free(*tree);
	*tree = NULL;
}
