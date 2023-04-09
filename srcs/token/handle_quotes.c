/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:54:20 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/09 21:33:29 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_line(char quote_char)
{
	char	*line;

	while (1)
	{
		line = readline(" > ");
		if (line == NULL)
			printf("Minishell: unexpected EOF while looking for \
				matching `%c'\n",
					quote_char);
		else
			return (line);
	}
}

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

// bash-5.2$ aaa"vv
// vv">>aaa
// bash: $'aaavv\nvv': command not found

// bash-5.2$ cat "
// > sdfsdf
// > dffsdf
// > ff" >> a >> aa "
// > adfffsdf" >> aa "
// > sdfsdf"
// cat:
// sdfsdf
// dffsdf
// ff: No such file or directory
// cat:
// adfffsdf: No such file or directory
// cat:
// sdfsdf: No such file or directory

void	line_to_buffer_until_the_quote_is_found(const char *line, int *i, char quote_char,
		char *buffer, int *buffer_index, int *find)
{
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

int	the_quote_is_found(int find, char **line, char *buffer,
		int *buffer_index)
{
	if (find)
		return (TRUE);
	free(*line);
	buffer[(*buffer_index)++] = '\n';
	return (FALSE);
}

void	read_remaining_line_and_handle_operators(const char *line, int *i,
		char quote_char, char *buffer, int *buffer_index,
		t_process_input_data *data)
{
	while (line[*i] != '\0' && line[*i] != quote_char)
	{
		if (!is_operator(line[*i]) && line[*i] != quote_char)
		{
			buffer[(*buffer_index)++] = line[*i];
			(*i)++;
		}
		else if (is_operator(line[*i]) && line[*i] != quote_char)
		{
			buffer_to_token_value(buffer, buffer_index, data->tokens,
					data->token_index);
			handle_operator(line, *i, data->tokens, data->token_index);
			(*i)++;
		}
	}
	buffer_to_token_value(buffer, buffer_index, data->tokens,
			data->token_index);
}

int	quote_char_is_found(const char *line, int *i, char *buffer,
		int *buffer_index)
{
	if (line[*i] == '\0')
		return (FALSE);
	while (line[*i] != '\0')
	{
		buffer[(*buffer_index)++] = line[*i];
		(*i)++;
	}
	buffer[(*buffer_index)++] = '\n';
	return (TRUE);
}

void read_input_until_finding_the_quote(char quote_char,
                                       char *buffer, int *buffer_index, t_process_input_data *data)
{
    char *line;
    int i;
    int find;

    buffer[(*buffer_index)++] = '\n';
    while (1)
    {
        line = get_line(quote_char);
        i = 0;
        find = FALSE;
		line_to_buffer_until_the_quote_is_found(line, &i, quote_char, buffer, buffer_index, &find);
        if (the_quote_is_found(find, &line, buffer, buffer_index))
        {
            read_remaining_line_and_handle_operators(line, &i, quote_char, buffer, buffer_index, data);
            if (!quote_char_is_found(line, &i, buffer, buffer_index))
				break ;
        }
    }
    if (find)
        free(line);
}