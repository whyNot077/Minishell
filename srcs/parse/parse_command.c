/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:08:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 21:20:17 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree_node	*parse_commands(t_token *tokens, int *index, char **env)
{
	t_token		*current_token;
	t_tree_node	*node;

	current_token = &tokens[*index];
	node = create_new_node(current_token);
	node->type = get_node_type(&current_token->value, env);
	node->data = current_token->value;
	(*index)++;
	return (node);
}

static t_tree_node	*parse_command_parts(t_token *tokens, int *index, char **env)
{
	t_tree_node	*node;

	node = parse_commands(tokens, index, env);
	if ((size_t)(*index) < tokens->token_count && next_token_is_io_redirect(tokens, *index))
	{
		node->left = parse_cmd_prefix(tokens, index, env);
	}
	if ((size_t)(*index) < tokens->token_count && tokens[*index].type == WORD)
	{
		node->right = parse_cmd_suffix(tokens, index, env);
	}
	return (node);
}

t_tree_node	*parse_command(t_token *tokens, int *index, char **env)
{
	t_tree_node	*node;
	t_token		*current_token;

	node = NULL;
	if ((size_t)(*index) >= tokens->token_count)
		return (node);
	current_token = &tokens[*index];
	if (current_token->type == WORD)
	{
		node = parse_command_parts(tokens, index, env);
	}
	else
	{
		printf("Error: syntax error near unexpected token `newline'\n");
		return (node);
	}
	return (node);
}
