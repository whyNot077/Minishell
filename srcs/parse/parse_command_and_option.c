/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_and_option.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:08:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/08 20:33:27 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	connect_command_node_to_tree(t_binarytree *tree, \
	t_tree_node *rightmost, t_tree_node *previous, t_tree_node *command_node)
{
	if (find_pipe(rightmost) == TRUE \
		|| rightmost->type == AND || rightmost->type == OR)
	{
		put_it_on_the_right_of_the_rightmost_node(tree, rightmost, previous, \
				command_node);
	}
	else if ((rightmost->type == WORD || rightmost->type == BUILTIN))
	{
		free(command_node);
	}
	else if (is_redirection(rightmost->type))
	{
		put_it_on_the_top_of_the_rightmost_node(tree, rightmost, previous, \
				command_node);
	}
}

void	add_command_to_the_tree(t_binarytree *tree, t_tree_node *command_node)
{
	t_tree_node	*current;
	t_tree_node	*previous;

	if (tree->root == NULL)
	{
		tree->root = command_node;
		return ;
	}
	else
	{
		get_rightmost_and_previous(tree, &current, &previous);
		connect_command_node_to_tree(tree, current, previous, command_node);
	}
}

void	parse_command_and_option(t_binarytree *tree, t_token *tokens,
		int *index)
{
	t_tree_node	*command_node;

	command_node = create_new_node(tokens[*index].value, tokens[*index].type);
	add_command_to_the_tree(tree, command_node);
	while (tokens[*index].type == WORD || tokens[*index].type == BUILTIN)
	{
		fill_command_structure(tree, tokens[*index].value);
		(*index)++;
	}
}
