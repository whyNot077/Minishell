/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:02:04 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/10 21:11:45 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_quote_from_front(char *value, size_t *start)
{
	int	quote;

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

void	find_the_quote_from_back(char *value, size_t *end, int quote)
{
	if (value == NULL || end == NULL)
		return ;
	while (*end > 0)
	{
		(*end)--;
		if (value[*end] == quote)
			break ;
	}
}

void	remove_quote_from_string(char *value, size_t start, size_t end)
{
	char	*new_value;
	size_t	i;
	size_t	j;

	if (value == NULL)
		return ;
	new_value = (char *)malloc(ft_strlen(value));
	if (!new_value)
		return ;
	i = 0;
	j = 0;
	while (value[i] != '\0')
	{
		if (i != start && i != end)
		{
			new_value[j] = value[i];
			j++;
		}
		i++;
	}
	new_value[j] = '\0';
	ft_memcpy(value, new_value, j + 1);
	free(new_value);
}

void	remove_quotes(char *value)
{
	int		quote;
	size_t	start;
	size_t	end;

	if (value == NULL)
		return ;
	start = 0;
	end = ft_strlen(value);
	while (start < end)
	{
		quote = find_quote_from_front(value, &start);
		if (quote == 0)
			return ;
		find_the_quote_from_back(value, &end, quote);
		remove_quote_from_string(value, start, end);
	}
}
