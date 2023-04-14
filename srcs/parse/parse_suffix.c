/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_suffix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:15:27 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 14:15:35 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree_node	*parse_cmd_suffix(t_token *tokens, int *index)
{
	t_tree_node	*node;
	t_tree_node	*temp_node;

	node = NULL;
	while (next_token_is_io_redirect(tokens, *index)
		|| tokens[*index].type == WORD)
	{
		if (next_token_is_io_redirect(tokens, *index))
		{
			temp_node = parse_io_redirect(tokens, index);
			if (!temp_node)
			{
				free_tree_nodes(node);
				return (NULL);
			}
		}
		else
		{
			temp_node = parse_commands(tokens, index);
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
