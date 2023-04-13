/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:16:53 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 14:27:14 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execution_order_traversal(tree_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == PIPE)
	{
		execution_order_traversal(node->left);
		execution_order_traversal(node->right);
	}
	else if (node->type == REDIRECT_OUT || node->type == REDIRECT_IN)
	{
		execution_order_traversal(node->left);
		execution_order_traversal(node->right);
	}
	else
	{
		printf("Data: %s, Type: %d\n", node->data, node->type);
		execution_order_traversal(node->left);
		execution_order_traversal(node->right);
	}
}

void	display_tree(binarytree *tree)
{
	if (tree == NULL || tree->root == NULL)
	{
		printf("Tree is empty\n");
		return ;
	}
	execution_order_traversal(tree->root);
}
