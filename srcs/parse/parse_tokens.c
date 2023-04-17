/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:30:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/17 14:46:37 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_tree_node	*parse_pipe_sequence(t_token *tokens, int *index, char **env)
{
	t_tree_node	*node;
	t_tree_node	*temp_node;

	node = simple_command(tokens, index, env);
	while ((size_t)(*index) < tokens->token_count \
		&& tokens[*index].type == PIPE)
	{
		temp_node = create_new_node(&tokens[*index]);
		temp_node->type = tokens[*index].type;
		(*index)++;
		temp_node->left = node;
		temp_node->right = simple_command(tokens, index, env);
		node = temp_node;
	}
	// printf("temp_node = %s\n", temp_node->data);
	// printf("temp_node->right = %s\n", temp_node->right->data);
	// printf("temp_node->left = %s\n", temp_node->left->data);
	return (node);
}

t_binarytree	*parse_tokens(t_token *tokens, char **env)
{
	t_binarytree *tree;
	int index;

	if (!tokens)
		return (NULL);
	tree = create_tree();
	index = 0;
	tree->root = parse_pipe_sequence(tokens, &index, env);
	return (tree);
}