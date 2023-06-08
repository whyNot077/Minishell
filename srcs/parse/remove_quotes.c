/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:02:04 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/07 22:06:13 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	find_quote_from_start(char *value, size_t *start)
{
	char	quote;

	quote = 0;
	if (value == NULL || start == NULL)
		return (quote);
	while (value[*start])
	{
		if (value[*start] == '\'' || value[*start] == '\"')
		{
			quote = value[*start];
			break ;
		}
		(*start)++;
	}
	return (quote);
}

static void	find_the_quote_from_end(char *value, size_t *end, int quote)
{
	if (value == NULL)
		return ;
	while (value[*end])
	{
		if (value[*end] == quote)
		{
			return ;
		}
		(*end)++;
	}
}

static void	copy_without_quotes(char *value, char *new_value, size_t start, \
		size_t end)
{
	char	quote;
	size_t	j;

	j = 0;
	while (value[start])
	{
		quote = find_quote_from_start(value, &start);
		if (start > end)
		{
			ft_memmove(new_value + j, value + end, start - end);
			j += start - end;
		}
		if (quote != 0)
		{
			end = start + 1;
			find_the_quote_from_end(value, &end, quote);
			ft_memmove(new_value + j, value + start + 1, end - start - 1);
			j += end - start - 1;
			start = end + 1;
		}
		end = start;
	}
	new_value[j] = '\0';
	free(value);
}

char	*remove_quotes(char *value)
{
	size_t	start;
	size_t	end;
	char	*new_value;

	if (value == NULL)
		return (NULL);
	new_value = (char *)malloc(ft_strlen(value) + 1);
	if (!new_value)
		return (NULL);
	start = 0;
	end = 0;
	copy_without_quotes(value, new_value, start, end);
	return (new_value);
}
