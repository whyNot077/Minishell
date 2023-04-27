/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:11:04 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/24 19:03:52 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_operator(const char *input, int i, t_array *list)
{
	char	operator_str[2];

	if (!is_space(input[i]) || (is_space(input[i]) \
		&& is_special_char(input[i - 1]) && is_special_char(input[i + 1])))
	{
		operator_str[0] = input[i];
		operator_str[1] = '\0';
		insert_token(list, ft_strdup(operator_str));
	}
}

static void	handle_remaining_buffer(char *buffer, int buffer_index, \
		t_array *list)
{
	if (buffer_index > 0)
	{
		buffer[buffer_index] = '\0';
		insert_token(list, ft_strdup(buffer));
	}
}

static void	handle_quote_char(t_process_input_data *data, int *i)
{
	char	quote_char;

	quote_char = data->input[*i];
	if (find_quote_to_the_end(data->buffer, &data->buffer_index, data->input, \
			i) == FALSE)
	{
		read_input_until_finding_the_quote(quote_char, data->buffer, \
				&data->buffer_index, data);
	}
}

static void	handle_operator_char(t_process_input_data *data, int *i)
{
	buffer_to_token_value(data->buffer, &data->buffer_index, data->list);
	handle_operator(data->input, *i, data->list);
}

void	process_input(t_array *list, const char *input)
{
	t_process_input_data	data;
	int						i;

	fill_data(&data, input, list);
	i = -1;
	while (data.input[++i] != '\0')
	{
		if (is_quote_char(data.input[i]))
		{
			handle_quote_char(&data, &i);
			if (data.input[i] == '\0')
				return ;
		}
		else if (is_operator(data.input[i]))
			handle_operator_char(&data, &i);
		else
			data.buffer[data.buffer_index++] = data.input[i];
	}
	handle_remaining_buffer(data.buffer, data.buffer_index, data.list);
}
