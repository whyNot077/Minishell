/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:30:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 14:07:26 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_node_type(char *value)
{
	if (value == NULL)
		return (ERROR);
	if (value[0] == '$')
		return (ENV);
	else if (value[0] == '-')
		return (OPTION);
	else
		return (WORD);
}

static t_tree_node	*parse_pipe_sequence(t_token *tokens, int *index)
{
	t_tree_node	*node;
	t_tree_node	*temp_node;

	node = parse_command(tokens, index);
	while ((size_t)(*index) < tokens->token_count \
		&& tokens[*index].type == PIPE)
	{
		temp_node = create_new_node(&tokens[*index]);
		temp_node->type = tokens[*index].type;
		(*index)++;
		temp_node->left = node;
		temp_node->right = parse_command(tokens, index);
		node = temp_node;
	}
	return (node);
}

t_binarytree	*parse_tokens(t_token *tokens)
{
	t_binarytree	*tree;
	int				index;

	if (!tokens)
		return (NULL);
	tree = create_tree();
	index = 0;
	tree->root = parse_pipe_sequence(tokens, &index);
	return (tree);
}
