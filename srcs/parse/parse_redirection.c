/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:24:15 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/18 19:09:58 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void parse_filename(t_binarytree *tree, char *value, int type, int *index)
{
	t_tree_node *filename_node;

	filename_node = create_new_node(value, type);
	tree->current_node->right = filename_node;
	(*index)++;
}

static void redirection_to_tree(t_binarytree *tree, t_tree_node	*new_node, int *index)
{
	t_tree_node *current_node;
	t_tree_node *parent_node;

	current_node = tree->current_node;
	if (current_node == NULL)
		tree->root = new_node;
	else if (current_node->type == PIPE)
	{
		current_node->right->parent = new_node;
		current_node->right = new_node;
	}
	else if (tree->root == current_node)
	{
		tree->root->parent = new_node;
		new_node->left = tree->root;
		tree->root = new_node;
	}
	else
	{
		parent_node = current_node->parent;
		if (parent_node->left == current_node)
			parent_node->left = new_node;
		else
			parent_node->right = new_node;
		current_node->parent = new_node;
		new_node->left = current_node;
	}
	tree->current_node = new_node;
	(*index)++;
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
	redirection_to_tree(tree, new_node, index);
	if (tokens[*index].type == WORD)
		parse_filename(tree, tokens[*index].value, tokens[*index].type, index);
	else
		printf("Error: Missing filename after '%s'\n", redirection);
}
