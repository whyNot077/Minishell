/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_and_option.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:08:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/20 16:59:35 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_command(t_binarytree *tree, char *value, int type)
{
	t_tree_node	*new_node;
	t_tree_node	*current_node;
	t_tree_node *redirection_node;

	current_node = tree->key_node;
	new_node = create_new_node(value, type);
	if (tree->root == NULL)
		tree->root = new_node;
	else
	{
		new_node->parent = current_node;
		if (current_node->type == PIPE)
			current_node->right = new_node;
		else if (is_redirection(current_node->type))
		{
			redirection_node = current_node;
			while (current_node->left != NULL)
			{
				current_node = current_node->left;
				new_node->parent = current_node;
			}
			current_node->left = new_node;
			tree->key_node = redirection_node;
			return ; 
		}
		else
		{
			while (current_node->left != NULL)
			{
				current_node = current_node->left;
				new_node->parent = current_node;
			}
			current_node->left = new_node;
		}
	}
	tree->key_node = new_node;
}

void	parse_command_and_option(t_binarytree *tree, t_token *tokens,
		int *index)
{
	t_tree_node	*current_node;

	current_node = tree->key_node;
	if (tokens[*index].type == WORD || tokens[*index].type == BUILTIN)
	{
		parse_command(tree, tokens[*index].value, tokens[*index].type);
		current_node = tree->key_node;
		(*index)++;
	}
	while ((size_t)*index < tokens->token_count
		&& tokens[*index].type == OPTION)
	{
		parse_option(tokens[*index].value, current_node);
		(*index)++;
	}
	if (tokens[*index].type == WORD || tokens[*index].type == BUILTIN)
		parse_command_and_option(tree, tokens, index);
}
