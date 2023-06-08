/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:36:02 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/08 11:39:07 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	connect_and_or_to_tree(t_binarytree *tree, \
	t_tree_node *rightmost, t_tree_node *previous, t_tree_node *and_or_node)
{
	if (find_pipe(rightmost) == TRUE || rightmost->type == AND || \
			rightmost->type == OR)
	{
		free(and_or_node);
		printf("Syntax error: unexpected '%s'\n", and_or_node->value);
		tree->syntex_error = TRUE;
	}
	else if (rightmost->type == WORD || rightmost->type == BUILTIN || \
		is_redirection(rightmost->type))
	{
		put_it_on_the_top_of_the_rightmost_node(tree, rightmost, previous, \
				and_or_node);
	}
}

static void	and_or_to_the_tree(t_binarytree *tree, t_tree_node *and_or_node, \
		int *index)
{
	t_tree_node	*current;
	t_tree_node	*previous;

	if (tree->root == NULL)
	{
		free(and_or_node);
		printf("Syntax error: unexpected '%s'\n", and_or_node->value);
		tree->syntex_error = TRUE;
		(*index)++;
	}
	else
	{
		get_rightmost_and_previous(tree, &current, &previous);
		if (current->type == PIPE || current->type == AND || \
				current->type == OR)
		{
			free(and_or_node);
			printf("Syntax error: unexpected '%s'\n", and_or_node->value);
			tree->syntex_error = TRUE;
			(*index)++;
			return ;
		}
		connect_and_or_to_tree(tree, current, previous, and_or_node);
	}
	(*index)++;
}

void	parse_and_or(t_binarytree *tree, t_token *tokens, int *index)
{
	int			type;
	char		*and_or;
	t_tree_node	*and_or_node;

	type = tokens[*index].type;
	and_or = tokens[*index].value;
	if (type != AND && type != OR)
		return ;
	and_or_node = create_new_node(and_or, type);
	and_or_to_the_tree(tree, and_or_node, index);
}
