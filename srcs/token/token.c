/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:09:12 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/24 18:21:12 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(char c)
{
	return (c == ' ' || c == '|' || c == '&' || c == '<' || c == '>');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r');
}

int	type_of_token(char	*value)
{
	if (ft_strncmp(value, ">>", 2) == 0)
		return (REDIRECT_APPEND);
	else if (ft_strncmp(value, "<<", 2) == 0)
		return (HEREDOC);
	else if (ft_strncmp(value, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(value, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(value, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(value, ">", 1) == 0)
		return (REDIRECT_OUT);
	else if (ft_strncmp(value, "<", 1) == 0)
		return (REDIRECT_IN);
	else
		return (WORD);
}

void	free_tokens(t_token **tokens_ptr)
{
	t_token	*tokens;
	int		i;

	tokens = *tokens_ptr;
	if (tokens == NULL)
		return ;
	i = 0;
	while (tokens[i].value != NULL)
	{
		free(tokens[i].value);
		tokens[i].value = NULL;
		i++;
	}
	free(tokens);
	*tokens_ptr = NULL;
}
