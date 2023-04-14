/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prefix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:23:31 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 19:38:49 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	next_token_is_io_redirect(t_token *tokens, int index)
{
	return ((size_t)index < tokens->token_count && \
			(tokens[index].type == REDIRECT_OUT \
					|| tokens[index].type == REDIRECT_IN \
					|| tokens[index].type == REDIRECT_APPEND \
					|| tokens[index].type == HEREDOC));
}

t_tree_node	*parse_cmd_prefix(t_token *tokens, int *index, char **env)
{
	t_tree_node	*node;
	t_tree_node	*temp_node;

	node = NULL;
	while (next_token_is_io_redirect(tokens, *index))
	{
		temp_node = parse_io_redirect(tokens, index, env);
		if (!temp_node)
		{
			free_tree_nodes(node);
			return (NULL);
		}
		if (!node)
		{
			node = temp_node;
		}
		else
		{
			temp_node->left = node;
			node = temp_node;
		}
	}
	return (node);
}
