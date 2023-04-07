/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:09:12 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/07 17:15:58 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(const char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->value = ft_strdup(value);
	return (token);
}

int	is_operator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == ';' || c == '(' \
		|| c == ')' || c == '|' || c == '&' || c == '<' || c == '>');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' \
		|| c == '\r');
}

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value != NULL)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}
