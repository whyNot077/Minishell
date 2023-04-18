/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heardoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:34:48 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/18 15:49:15 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heardoc_to_the_tree(t_binarytree *tree, t_tree_node *new_node,
		int *index)
{
	t_tree_node	*current_node;

	current_node = tree->current_node;
	if (current_node->right == NULL)
		current_node->right = new_node;
	else
	{
		new_node->left = current_node->right;
		current_node->right = new_node;
	}
	tree->current_node = new_node;
	(*index)++;
}

static void	parse_here_end(t_binarytree *tree, char *value, int type)
{
	t_tree_node	*here_end;
	t_tree_node	*heredoc_node;

	here_end = create_new_node(value, type);
	heredoc_node = tree->current_node;
	heredoc_node->right = here_end;
	tree->current_node = here_end;
}

void	parse_heredoc(t_binarytree *tree, t_token *tokens, int *index)
{
	int			type;
	char		*heredoc_symbol;
	t_tree_node	*new_node;

	type = tokens[*index].type;
	heredoc_symbol = tokens[*index].value;
	if (type != HEREDOC)
		return ;
	new_node = create_new_node(heredoc_symbol, type);
	heardoc_to_the_tree(tree, new_node, index);
	if (tokens[*index].type == WORD)
		parse_here_end(tree, tokens[*index].value, tokens[*index].type);
	else
		printf("Error: Missing here_end after '%s'\n", heredoc_symbol);
}
