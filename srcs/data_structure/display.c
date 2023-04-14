/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:16:53 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 20:16:17 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char	*node_type_to_str(int node_type)
{
	if (node_type == PIPE)
		return ("PIPE");
	else if (node_type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (node_type == REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (node_type == REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	else if (node_type == HEREDOC)
		return ("HEREDOC");
	else if (node_type == AND)
		return ("AND");
	else if (node_type == OR)
		return ("OR");
	else if (node_type == WORD)
		return ("WORD");
	else if (node_type == OPTION)
		return ("OPTION");
	else if (node_type == BUILTIN)
		return ("BUILTIN");
	return ("UNKNOWN");
}

void	display_tree_helper(t_tree_node *node, int depth)
{
	if (node == NULL)
	{
		return ;
	}
	for (int i = 0; i < depth; ++i)
	{
		printf("  ");
	}
	printf("%s, ", node_type_to_str(node->type));
	if (node->data)
	{
		printf("execute = (%s)", node->data);
	}
	printf("\n");
	display_tree_helper(node->left, depth + 1);
	display_tree_helper(node->right, depth + 1);
}

void	display_tree(t_tree_node *node)
{
	display_tree_helper(node, 0);
}