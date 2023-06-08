/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:07:13 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/07 21:50:13 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	copy_tokens(t_token *src_tokens, t_token *new_tokens,
		size_t *start_end, size_t *index)
{
	size_t	i;

	i = start_end[0];
	while (i < start_end[1])
	{
		new_tokens[*index].value = ft_strdup(src_tokens[i].value);
		new_tokens[*index].type = type_of_token(src_tokens[i].value);
		free(src_tokens[i].value);
		get_node_type(new_tokens, *index);
		i++;
		(*index)++;
	}
}

void	copy_tokens_to_new_tokens(t_token *new_tokens, t_token *tokens,
		t_token *env_tokens, size_t index)
{
	size_t	i;
	size_t	start_end[2];
	size_t	env_token_count;
	size_t	token_count;

	i = 0;
	env_token_count = env_tokens->token_count;
	token_count = tokens->token_count;
	start_end[0] = 0;
	start_end[1] = index;
	copy_tokens(tokens, new_tokens, start_end, &i);
	start_end[0] = 0;
	start_end[1] = env_token_count;
	copy_tokens(env_tokens, new_tokens, start_end, &i);
	start_end[0] = index + 1;
	start_end[1] = token_count;
	copy_tokens(tokens, new_tokens, start_end, &i);
	new_tokens[i].value = NULL;
}
