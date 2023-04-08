/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:13:45 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/08 14:14:11 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_special_token(char *token)
{
	if (token == NULL)
		return (ERROR);
	return (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, "<", 1) == 0
		|| ft_strncmp(token, "&", 1) == 0 || ft_strncmp(token, "|", 1) == 0);
}

int	num_of_special_tokens(t_token *tokens, int token_index)
{
	int	i;
	int	num_of_special_tokens;

	i = -1;
	num_of_special_tokens = 0;
	while (++i < token_index)
	{
		if (is_special_token(tokens[i].value))
			if (++i < token_index && is_special_token(tokens[i].value))
				if (tokens[i - 1].type == tokens[i].type)
					num_of_special_tokens++;
	}
	return (num_of_special_tokens);
}
