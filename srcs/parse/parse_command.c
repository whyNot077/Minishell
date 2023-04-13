/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:08:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 19:08:54 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

tree_node	*parse_word(t_token *tokens, int *index)
{
	t_token		*current_token;
	tree_node	*node;

	current_token = &tokens[*index];
	node = create_new_node(current_token);
	node->type = get_node_type(current_token->value);
	(*index)++;
	return (node);
}

tree_node	*parse_pipe(t_token *tokens, int *index)
{
	tree_node	*node;

	node = create_new_node(&tokens[*index]);
	node->type = PIPE;
	(*index)++;
	node->right = parse_command(tokens, index);
	return (node);
}

tree_node	*parse_redirect(t_token *tokens, int *index)
{
	tree_node	*node;

	node = create_new_node(&tokens[*index]);
	node->type = REDIRECT_OUT;
	(*index)++;
	node->right = parse_command(tokens, index);
	return (node);
}

tree_node	*parse_command(t_token *tokens, int *index)
{
	tree_node	*node;
	t_token		*current_token;
	t_token		*next_token;

	node = NULL;
	if ((size_t)*index >= tokens->token_count)
		return (NULL);
	current_token = &tokens[*index];
	if (current_token->type == WORD || current_token->type == ENV
		|| current_token->type == OPTION)
	{
		node = parse_word(tokens, index);
		next_token = &tokens[*index];
		if ((size_t)*index < tokens->token_count &&
			(next_token->type == PIPE || next_token->type == REDIRECT_OUT
					|| next_token->type == REDIRECT_IN))
		{
			if (next_token->type == PIPE)
			{
				node->right = parse_pipe(tokens, index);
			}
			else
			{
				node->right = parse_redirect(tokens, index);
			}
		}
	}
	return (node);
}
