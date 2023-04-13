/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:08:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 20:54:11 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	next_token_is_option(t_token *tokens, int index)
{
	return ((size_t)index < tokens->token_count \
		&& get_node_type(tokens[index].value) == OPTION);
}

int	next_token_is_pipe(t_token *tokens, int index)
{
	return ((size_t)index < tokens->token_count && tokens[index].type == PIPE);
}

int	next_token_is_redirect(t_token *tokens, int index)
{
	return ((size_t)index < tokens->token_count \
		&& (tokens[index].type == REDIRECT_OUT \
			|| tokens[index].type == REDIRECT_IN));
}

int next_token_is_env(t_token *tokens, int index)
{
    return ((size_t)index < tokens->token_count \
		&& get_node_type(tokens[index].value) == ENV);
}

tree_node	*parse_command(t_token *tokens, int *index)
{
	tree_node	*node;
	t_token		*current_token;
	t_token		*next_token;

	node = NULL;
	if ((size_t)*index >= tokens->token_count)
		return (node);
	current_token = &tokens[*index];
	if (current_token->type == WORD || current_token->type == ENV \
		|| current_token->type == OPTION)
	{
		node = parse_commands(tokens, index);
		next_token = &tokens[*index];
		if (next_token_is_option(tokens, *index))
		{
			node->left = parse_commands(tokens, index);
			next_token = &tokens[*index];
		}
		if (next_token_is_env(tokens, *index))
		{
			node->left = parse_commands(tokens, index);
			next_token = &tokens[*index];
		}
		if (next_token_is_pipe(tokens, *index))
		{
			node->right = parse_pipe(tokens, index);
			if (node->right == NULL)
				return (node);
		}
		else if (next_token_is_redirect(tokens, *index))
		{
			node->right = parse_redirect(tokens, index);
			if (node->right == NULL)
				return (node);
		}
	}
	else
	{
		printf("Error: syntax error near unexpected token `newline'\n");
		return (node);
	}
	return (node);
}
