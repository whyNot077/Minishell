/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:16:53 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 11:47:35 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char	*node_type_to_str(int node_type)
{
	if (node_type == PIPE)
		return ("PIPE");
	if (node_type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (node_type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (node_type == REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	if (node_type == HEREDOC)
		return ("HEREDOC");
	if (node_type == AND)
		return ("AND");
	if (node_type == OR)
		return ("OR");
	if (node_type == WORD)
		return ("WORD");
	if (node_type == ENV)
		return ("ENV");
	if (node_type == OPTION)
		return ("OPTION");
	return ("UNKNOWN");
}

void	display_tree_helper(tree_node *node, int depth)
{
	if (node == NULL)
	{
		return ;
	}
	for (int i = 0; i < depth; ++i)
	{
		printf("  ");
	}
	printf("%s", node_type_to_str(node->type));
	if (node->data)
	{
		printf(" (%s)", node->data);
	}
	printf("\n");
	display_tree_helper(node->left, depth + 1);
	display_tree_helper(node->right, depth + 1);
}

void	display_tree(tree_node *node)
{
	display_tree_helper(node, 0);
}