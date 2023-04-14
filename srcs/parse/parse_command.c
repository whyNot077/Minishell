/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:08:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 14:08:23 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree_node	*parse_commands(t_token *tokens, int *index)
{
	t_token		*current_token;
	t_tree_node	*node;

	current_token = &tokens[*index];
	node = create_new_node(current_token);
	node->type = get_node_type(current_token->value);
	(*index)++;
	return (node);
}

t_tree_node	*parse_command(t_token *tokens, int *index)
{
	t_tree_node	*node;
	t_token		*current_token;

	node = NULL;
	if ((size_t)(*index) >= tokens->token_count)
	{
		return (node);
	}
	current_token = &tokens[*index];
	if (current_token->type == WORD)
	{
		node = parse_commands(tokens, index);
		if ((size_t)(*index) < tokens->token_count \
			&& tokens[*index].type != PIPE)
		{
			node->left = parse_cmd_prefix(tokens, index);
		}
		if ((size_t)(*index) < tokens->token_count \
			&& tokens[*index].type != PIPE)
		{
			node->right = parse_cmd_suffix(tokens, index);
		}
	}
	else
	{
		printf("Error: syntax error near unexpected token `newline'\n");
		return (node);
	}
	return (node);
}
