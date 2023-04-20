/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:34:48 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/20 18:27:13 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heardoc_to_the_tree(t_binarytree *tree, t_tree_node *new_node,
		int *index)
{
	t_tree_node	*dummy;

	dummy = tree->key_node;
	while (dummy->left != NULL)
		dummy = dummy->left;
	dummy->left = new_node;
	new_node->parent = dummy;
	(*index)++;
}

static void	parse_here_end(t_binarytree *tree, char *value, \
	int type, t_tree_node *heredoc_node)
{
	t_tree_node	*here_end;

	here_end = create_new_node(value, type);
	heredoc_node = tree->key_node;
	heredoc_node->right = here_end;
	here_end->parent = heredoc_node;
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
		parse_here_end(tree, tokens[*index].value, tokens[*index].type, new_node);
	else
		printf("Error: Missing here_end after '%s'\n", heredoc_symbol);
}
