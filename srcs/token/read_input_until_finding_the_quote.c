/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_until_finding_the_quote.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:52:53 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/12 14:54:02 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_buffer_until_the_quote_is_found(const char *line, int *i,
		t_find *quote, t_process_input_data *data)
{
	char	*buffer;
	int		*buffer_index;
	char	quote_char;
	int		*find;

	buffer = data->buffer;
	buffer_index = &data->buffer_index;
	quote_char = quote->quote_char;
	find = quote->find;
	while (line[*i] != '\0')
	{
		buffer[(*buffer_index)++] = line[*i];
		if (line[(*i)++] == quote_char)
		{
			*find = TRUE;
			break ;
		}
	}
}

static int	the_quote_is_found(int find, char **line, char *buffer,
		int *buffer_index)
{
	if (find)
		return (TRUE);
	free(*line);
	(*line) = NULL;
	buffer[(*buffer_index)++] = '\n';
	return (FALSE);
}

static void	read_remaining_line_dealing_operators(const char *line, int *i,
		t_process_input_data *data)
{
	char	*buffer;
	int		*buffer_index;

	buffer = data->buffer;
	buffer_index = &data->buffer_index;
	while (line[*i] != '\0' && !is_quote_char(line[*i]))
	{
		if (!is_operator(line[*i]) && !is_quote_char(line[*i]))
		{
			buffer[(*buffer_index)++] = line[*i];
			(*i)++;
		}
		else if (is_operator(line[*i]) && !is_quote_char(line[*i]))
		{
			buffer_to_token_value(buffer, buffer_index, data->list);
			handle_operator(line, *i, data->list);
			(*i)++;
		}
	}
	buffer_to_token_value(buffer, buffer_index, data->list);
}

int	another_quote_is_found(const char *line, int *i, t_process_input_data *data,
		char *quote_char)
{
	char	*buffer;
	int		*buffer_index;

	buffer = data->buffer;
	buffer_index = &data->buffer_index;
	if (line[*i] == '\0')
		return (FALSE);
	(*quote_char) = line[*i];
	while (line[*i] != '\0')
	{
		buffer[(*buffer_index)++] = line[*i];
		(*i)++;
	}
	buffer[(*buffer_index)++] = '\n';
	return (TRUE);
}

void	read_input_until_finding_the_quote(char quote_char,
										char *buffer,
										int *buffer_index,
										t_process_input_data *data)
{
	char	*line;
	int		i;
	int		find;
	t_find	quote;

	buffer[(*buffer_index)++] = '\n';
	while (1)
	{
		line = get_line(quote_char);
		i = 0;
		find = FALSE;
		quote.quote_char = quote_char;
		quote.find = &find;
		add_buffer_until_the_quote_is_found(line, &i, &quote, data);
		if (the_quote_is_found(find, &line, buffer, buffer_index))
		{
			read_remaining_line_dealing_operators(line, &i, data);
			if (!another_quote_is_found(line, &i, data, &quote_char))
				break ;
			else
				free(line);
		}
	}
	if (find)
		free(line);
}
