/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:13:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 19:44:35 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_tree_node	*create_redirect_node(t_token *tokens, int *index)
{
	t_tree_node	*node;

	if (tokens[*index].type == REDIRECT_OUT || \
		tokens[*index].type == REDIRECT_IN || \
		tokens[*index].type == REDIRECT_APPEND)
	{
		node = create_new_node(&tokens[*index]);
		node->type = tokens[*index].type;
		(*index)++;
	}
	else if (tokens[*index].type == HEREDOC)
	{
		node = create_new_node(&tokens[*index]);
		node->type = tokens[*index].type;
		(*index)++;
	}
	else
	{
		printf("Error: syntax error near unexpected token %s\n", \
				tokens[*index].value);
		return (NULL);
	}
	return (node);
}

static t_tree_node	*process_token_after_redirect(t_token *tokens, \
	int *index, t_tree_node *node)
{
	if (tokens[*index].value == NULL)
	{
		free(node);
		printf("Error: syntax error near unexpected token %s\n", \
				tokens[*index - 1].value);
		return (NULL);
	}
	else if (tokens[*index].type != WORD)
	{
		free(node);
		printf("Error: syntax error near unexpected token %s\n", \
				tokens[*index].value);
		return (NULL);
	}
	return (node);
}

t_tree_node	*parse_io_redirect(t_token *tokens, int *index, char **env)
{
	t_tree_node	*node;

	if (tokens[*index].type == REDIRECT_OUT || \
		tokens[*index].type == REDIRECT_IN || \
		tokens[*index].type == REDIRECT_APPEND || \
		tokens[*index].type == HEREDOC)
	{
		node = create_redirect_node(tokens, index);
		node = process_token_after_redirect(tokens, index, node);
		if (!node)
		{
			return (NULL);
		}
		node->right = parse_commands(tokens, index, env);
	}
	else
	{
		printf("Error: syntax error near unexpected token %s\n", \
				tokens[*index].value);
		return (NULL);
	}
	return (node);
}
