/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:23:31 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 19:51:35 by minkim3          ###   ########.fr       */
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

tree_node	*parse_option(t_token *tokens, int *index)
{
	t_token		*current_token;
	tree_node	*node;

	current_token = &tokens[*index];
	node = create_new_node(current_token);
	node->type = get_node_type(current_token->value);
	(*index)++;
	return (node);
}