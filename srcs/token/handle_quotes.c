/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:54:20 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/10 21:44:26 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_quote_to_the_end(char *buffer, int *buffer_index, const char *input,
		int *i)
{
	char	quote_char;

	quote_char = input[*i];
	buffer[(*buffer_index)++] = quote_char;
	(*i)++;
	while (input[*i] != '\0' && input[*i] != quote_char)
	{
		buffer[(*buffer_index)++] = input[*i];
		(*i)++;
	}
	if (input[*i] == quote_char)
	{
		buffer[(*buffer_index)++] = quote_char;
		buffer[(*buffer_index)] = '\0';
		return (TRUE);
	}
	return (FALSE);
}

int	is_quote_char(char c)
{
	return (c == '"' || c == '\'');
}

char	*get_line(char quote_char)
{
	char	*line;

	while (1)
	{
		line = readline(" > ");
		if (line == NULL)
			printf("Minishell: unexpected EOF while looking for \
				matching `%c'\n", quote_char);
		else
			return (line);
	}
}
