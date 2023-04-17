/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:08:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/17 16:30:55 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree_node	*command(t_token *tokens, int *index, char **env)
{
	t_token		*current_token;
	t_tree_node	*node;

	current_token = &tokens[*index];
	// if (get_node_type(&tokens[(*index) + 1].value, env) == OPTION)
	// {
		
	// 	(*index)++;
	// }
	node = create_new_node(current_token);
	node->type = get_node_type(&current_token->value, env);
	node->data = current_token->value;
	(*index)++;
	return (node);
}

static int	is_io_redirect(t_token *tokens)
{
	return (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT \
		|| tokens->type == REDIRECT_APPEND || tokens->type == HEREDOC);
}

t_tree_node	*simple_command(t_token *tokens, int *index, char **env)
{
	t_tree_node	*node;
	t_token		*current_token;

	node = NULL;
	if ((size_t)(*index) >= tokens->token_count)
		return (node);
	current_token = &tokens[*index];
	if (is_io_redirect(current_token) == TRUE)
	{
		node = parse_cmd_prefix(tokens, index, env);
	}
	if (current_token->type == WORD)
	{
		node = command(tokens, index, env);
	}
	if (is_io_redirect(current_token) == TRUE)
	{
		node = parse_cmd_suffix(tokens, index, env);
	}
	else
	{
		printf("Error: syntax error near unexpected token `newline'\n");
		return (node);
	}
	return (node);
}
