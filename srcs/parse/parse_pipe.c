/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:39:42 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/20 19:42:21 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void pipe_to_the_tree(t_binarytree *tree, t_tree_node *pipe_node, int *index)
{
	t_tree_node	*dummy;

	if (tree->root == NULL)
		tree->root = pipe_node;
	else if (tree->root->type == PIPE)
	{
		dummy = tree->root;
		while (dummy->right->type == PIPE)
			dummy = dummy->right;
		pipe_node->parent = dummy;
		pipe_node->left = dummy->right;
		dummy->right = pipe_node;
	}
	else
	{
		tree->root->parent = pipe_node;
		pipe_node->left = tree->root;
		tree->root = pipe_node;
	}
	tree->key_node = pipe_node;
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
	if (tokens[*index].type == WORD || tokens[*index].type == BUILTIN)
		parse_command_and_option(tree, tokens, index);
	else if (tokens[*index].type == PIPE)
		printf("syntax error near unexpected token `|'\n");
}
