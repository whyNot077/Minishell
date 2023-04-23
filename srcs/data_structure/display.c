/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:16:53 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/23 19:29:16 by minkim3          ###   ########.fr       */
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

void display_tree_helper(t_tree_node *node, int depth, char *branch)
{
    if (node == NULL)
        return;
    for (int i = 0; i < depth; ++i)
        printf("  ");
    printf("%s", branch);
    printf("%s, ", node_type_to_str(node->type));
    if (node->value)
    {
        printf("execute = ");
        if (node->type == WORD)
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
				printf("filename = (%s)", node->filename);
		}
    }
    printf("\n");
    if (node->left)
        display_tree_helper(node->left, depth + 1, "|--  left,  ");
    if (node->right)
        display_tree_helper(node->right, depth + 1, "`--  right,  ");
}

void inorder_traverse(t_tree_node *node)
{
    if (node == NULL)
    {
        return;
    }

	inorder_traverse(node->left);

	printf("execute = ");
	if (node->type == WORD)
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

    inorder_traverse(node->right);
}


void	display_tree(t_tree_node *node)
{
	printf("\ndisplay tree\n");
	display_tree_helper(node, 0, "");
	printf("\ninorder traverse\n");
	inorder_traverse(node);
}