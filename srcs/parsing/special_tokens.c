/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:55:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/07 18:24:22 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_special_token(char *token)
{
	if (token == NULL)
		return (ERROR);
	return (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0
		|| ft_strcmp(token, "&") == 0 || ft_strcmp(token, "|") == 0);
}

static void	num_of_special_tokens(t_token *tokens, int token_index)
{
	int i;
	int	num_of_special_tokens;

	i = -1;
	num_of_special_tokens = 0;
	while (++i < token_index)
	{
		if (is_special_token(tokens[i].value))
			if (is_special_token(tokens[++i].value) && i < token_index)
				if (ft_strcmp(tokens[i - 1].value, tokens[i].value) == 0)
					if (is_special_token(tokens[++i].value) != TRUE && i < token_index)
						num_of_special_tokens++;
	}
	printf("num_of_special_tokens: %d\n", num_of_special_tokens);
}

void	special_tokens(t_token *tokens, int token_index)
{
	// ">> << && ||"
	num_of_special_tokens(tokens, token_index);
	
}