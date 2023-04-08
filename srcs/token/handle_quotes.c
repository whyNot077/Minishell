/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:54:20 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/08 21:27:41 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_line(char quote_char)
{
	char	*line;

	while (1)
	{
		line = readline(" >");
		if (line == NULL)
			printf("Minishell: unexpected EOF while looking for \
				matching `%c'\n", quote_char);
		else
			return (line);
	}
}

int	find_quote_to_the_end(char *buffer, int *buffer_index, \
	const char *input, int *i)
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

void	read_input_until_finding_the_quote(char quote_char, \
	char *buffer, int *buffer_index)
{
	char	*line;
	int		i;
	int		find;

	find = FALSE;
	buffer[(*buffer_index)++] = '\n';
	while (!find)
	{
		line = get_line(quote_char);
		i = 0;
		while (line[i] != '\0')
		{
			if (line[i] == quote_char)
				find = TRUE;
			else
				buffer[(*buffer_index)++] = line[i];
			i++;
		}
		if (!find)
			buffer[(*buffer_index)++] = '\n';
		free(line);
	}
	buffer[(*buffer_index)++] = quote_char;
}
