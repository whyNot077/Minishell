/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:24:15 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/07 19:45:21 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_filename(t_tree_node *new_node, char *value, int *index)
{
	new_node->filename = ft_strdup(value);
	(*index)++;
}

static void	connect_redirection_node(t_binarytree *tree, \
t_tree_node *rightmost, t_tree_node *previous, t_tree_node *redirection_node)
{
	if (find_pipe(rightmost) == TRUE)
	{
		rightmost->right = redirection_node;
	}
	else if ((rightmost->type == WORD || rightmost->type == BUILTIN))
	{
		put_it_on_the_left_of_the_rightmost_node(tree, rightmost, previous, \
				redirection_node);
	}
	else if (is_redirection(rightmost->type))
	{
		put_it_on_the_top_of_the_rightmost_node(tree, rightmost, previous, \
				redirection_node);
	}
	else if (rightmost->type == AND || rightmost->type == OR)
	{
		put_it_on_the_right_of_the_rightmost_node(tree, rightmost, previous, \
				redirection_node);
	}
}

static void	redirection_to_tree(t_binarytree *tree, t_tree_node *redirection)
{
	t_tree_node	*current;
	t_tree_node	*previous;

	if (tree->root == NULL)
	{
		tree->root = redirection;
	}
	else
	{
		get_rightmost_and_previous(tree, &current, &previous);
		connect_redirection_node(tree, current, previous, redirection);
	}
}

void	parse_redirection(t_binarytree *tree, t_token *tokens, int *index)
{
	int			type;
	char		*redirection;
	t_tree_node	*new_node;

	type = tokens[*index].type;
	redirection = tokens[*index].value;
	if (is_redirection(type) == 0)
		return ;
	new_node = create_new_node(redirection, type);
	redirection_to_tree(tree, new_node);
	(*index)++;
	if (tokens[*index].type == WORD)
		parse_filename(new_node, tokens[*index].value, index);
	else
	{
		printf("Error: Missing filename after '%s'\n", redirection);
		tree->syntex_error = TRUE;
	}
}
