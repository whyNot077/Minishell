/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:39:42 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/07 14:13:48 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	connect_pipe_node_to_tree(t_binarytree *tree, \
	t_tree_node *rightmost, t_tree_node *previous, t_tree_node *pipe_node)
{
	if (find_pipe(rightmost) == TRUE)
	{
		free(pipe_node);
		printf("Syntax error: unexpected pipe '|'\n");
		tree->syntex_error = TRUE;
	}
	else if (rightmost->type == WORD || rightmost->type == BUILTIN)
	{
		pipe_node->left = rightmost->left;
		rightmost->left = pipe_node;
	}
	else if (is_redirection(rightmost->type))
	{
		pipe_node->left = rightmost;
		if (previous)
			previous->right = pipe_node;
		else
			tree->root = pipe_node;
	}
}

static void	pipe_to_the_tree(t_binarytree *tree, t_tree_node *pipe_node, \
		int *index)
{
	t_tree_node	*current;
	t_tree_node	*previous;

	if (tree->root == NULL)
	{
		free(pipe_node);
		printf("Syntax error: unexpected pipe '|'\n");
		tree->syntex_error = TRUE;
		(*index)++;
	}
	else
	{
		get_rightmost_and_previous(tree, &current, &previous);
		if (current->type == PIPE || current->type == AND || \
				current->type == OR)
		{
			free(pipe_node);
			printf("Syntax error: unexpected pipe '|'\n");
			tree->syntex_error = TRUE;
			(*index)++;
			return ;
		}
		connect_pipe_node_to_tree(tree, current, previous, pipe_node);
	}
	(*index)++;
}

void	parse_pipe(t_binarytree *tree, t_token *tokens, int *index)
{
	int			type;
	char		*pipe;
	t_tree_node	*pipe_node;

	type = tokens[*index].type;
	pipe = tokens[*index].value;
	if (type != PIPE)
		return ;
	pipe_node = create_new_node(pipe, type);
	pipe_to_the_tree(tree, pipe_node, index);
}
