/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:54:20 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/08 18:31:43 by minkim3          ###   ########.fr       */
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
			printf("Minishell: unexpected EOF while looking for matching `%c'\n",
					quote_char);
		else
			return (line);
	}
}

static void	read_input_until_find_quote(char quote_char, char *buffer,
		int *buffer_index)
{
	char	*line;
	int		i;
	int		flag;

	flag = 0;
	while (1)
	{
		line = get_line(quote_char);
		i = 0;
		while (line[i] != '\0')
		{
			if (line[i] == quote_char)
				flag = 1;
			else
				buffer[(*buffer_index)++] = line[i];
			i++;
		}
		free(line);
		if (flag == 1)
		{
			buffer[(*buffer_index)++] = quote_char;
			break ;
		}
	}
}

void	handle_quotes(const char *input, int *i, char *buffer,
		int *buffer_index)
{
	char	quote_char;

	quote_char = input[*i];
	buffer[(*buffer_index)++] = quote_char;
	(*i)++;
	while (input[*i] != quote_char)
	{
		if (input[*i] == '\0')
		{
			read_input_until_find_quote(quote_char, buffer, buffer_index);
			return ;
		}
		else
			buffer[(*buffer_index)++] = input[*i];
		(*i)++;
	}
	buffer[(*buffer_index)++] = quote_char;
}
