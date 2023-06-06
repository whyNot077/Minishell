/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:24:15 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/06 15:57:32 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_filename(t_tree_node *new_node, char *value, int *index)
{
	new_node->filename = ft_strdup(value);
	(*index)++;
}

static void	connect_redirection_node(t_binarytree *tree, t_tree_node *rightmost, \
		t_tree_node *previous, t_tree_node *redirection_node)
{
	if (find_pipe(rightmost) == TRUE)
	{
		rightmost->right = redirection_node;
	}
	else if ((rightmost->type == WORD || rightmost->type == BUILTIN))
	{
		redirection_node->left = rightmost->left;
		rightmost->left = redirection_node;
	}
	else if (is_redirection(rightmost->type))
	{
		redirection_node->left = rightmost;
		if (previous)
			previous->right = redirection_node;
		else
			tree->root = redirection_node;
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
		current = tree->root;
		previous = NULL;
		while (current->right)
		{
			previous = current;
			current = current->right;
		}
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
