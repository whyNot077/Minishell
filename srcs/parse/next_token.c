/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:55:58 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 20:56:12 by minkim3          ###   ########.fr       */
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