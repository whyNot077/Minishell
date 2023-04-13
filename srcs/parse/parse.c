/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:30:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 14:33:08 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_node_type(char *value)
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

static tree_node	*parse(t_token *tokens, int *index)
{
	t_token		*current_token;
	tree_node	*node;

	if ((size_t)*index >= tokens->token_count)
		return (NULL);
	current_token = &tokens[*index];
	node = create_new_node(current_token);
	if (current_token->type == WORD || current_token->type == ENV\
			|| current_token->type == OPTION)
	{
		node->type = get_node_type(current_token->value);
		(*index)++;
		node->left = parse(tokens, index);
	}
	else if (current_token->type == PIPE || current_token->type == REDIRECT_OUT\
			|| current_token->type == REDIRECT_IN)
	{
		node->type = current_token->type;
		(*index)++;
		node->right = parse(tokens, index);
	}
	return (node);
}

binarytree	*parse_tokens(t_token *tokens)
{
	binarytree	*tree;
	int			index;

	if (!tokens)
		return (NULL);
	tree = create_tree();
	index = 0;
	tree->root = parse(tokens, &index);
	return (tree);
}
