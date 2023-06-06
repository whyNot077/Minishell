/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:36:02 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/06 16:55:03 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_and_or(int type)
{
	return (type == AND || type == OR);
}

void	parse_and_or(t_binarytree *tree, t_token *tokens, int *index)
{
	t_tree_node	*rightmost_node;
	t_tree_node	*command_node;

	if (tree->root == NULL)
	{
		printf("Syntax error: tree is empty.\n");
		tree->syntex_error = TRUE;
		(*index)++;
		return ;
	}
	rightmost_node = find_rightmost_node(tree->root);
	if (is_and_or(rightmost_node->type))
	{
		printf("Syntax error: rightmost node is AND/OR.\n");
		tree->syntex_error = TRUE;
		(*index)++;
		return ;
	}
	command_node = create_new_node(tokens[*index].value, tokens[*index].type);
	rightmost_node->right = command_node;
	(*index)++;
}
