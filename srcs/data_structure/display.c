/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:16:53 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/05 19:32:38 by hyojocho         ###   ########.fr       */
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
	else if (node_type == BUILTIN)
		return ("BUILTIN");
	return ("UNKNOWN");
}

void inorder_traverse(t_tree_node *node, char **env, t_execute *execute)
{
    if (node == NULL)
    {
        return;
    }
	inorder_traverse(node->left, env, execute);
	printf("%s, ", node_type_to_str(node->type));
	printf("execute = ");
	if (node->type == WORD || node->type == BUILTIN)
	{
		if (node->command)
		{
			for (int i = 0; node->command[i]; ++i)
			{
				printf("(%s)", node->command[i]);
			}
		}
		else
		{
			printf("(%s)", node->value);
		}
	}
	else
	{
		printf("(%s)", node->value);
		if (node->filename)
			printf(", filename = (%s)", node->filename);
	}
    printf("\n");

    inorder_traverse(node->right, env, execute);
}


void	display_tree(t_tree_node *node, char **env, t_execute *execute)
{
	printf("\ninorder traverse\n");
	inorder_traverse(node, env, execute);
}