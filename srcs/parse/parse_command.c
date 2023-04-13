/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:08:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 19:50:01 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	next_token_is_option(t_token *tokens, int index)
{
	return ((size_t)index < tokens->token_count
		&& tokens[index].type == OPTION);
}

int	next_token_is_pipe(t_token *tokens, int index)
{
	return ((size_t)index < tokens->token_count && tokens[index].type == PIPE);
}

int	next_token_is_redirect(t_token *tokens, int index)
{
	return ((size_t)index < tokens->token_count
		&& (tokens[index].type == REDIRECT_OUT
			|| tokens[index].type == REDIRECT_IN));
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
		if (next_token_is_option(tokens, *index))
		{
			printf("option = %s\n", next_token->value);
			node->left = parse_option(tokens, index);
			next_token = &tokens[*index];
		}
		if (next_token_is_pipe(tokens, *index))
		{
			node->right = parse_pipe(tokens, index);
		}
		else if (next_token_is_redirect(tokens, *index))
		{
			node->right = parse_redirect(tokens, index);
		}
	}
	else
	{
		printf("Error: unexpected token %s\n", current_token->value);
		exit(1);
	}
	return (node);
}