/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:11:04 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/10 14:35:48 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_operator(const char *input, int i, t_token *tokens,
		int *token_index)
{
	char	operator_str[2];

	if (!is_space(input[i]) || (is_space(input[i]) \
		&& is_special_char(input[i - 1]) && is_special_char(input[i + 1])))
	{
		operator_str[0] = input[i];
		operator_str[1] = '\0';
		tokens[(*token_index)++].value = ft_strdup(operator_str);
		type_of_token(tokens, *token_index - 1);
	}
}

static void	handle_remaining_buffer(char *buffer, int buffer_index,
		t_token *tokens, int *token_index)
{
	if (buffer_index > 0)
	{
		buffer[buffer_index] = '\0';
		tokens[(*token_index)++].value = ft_strdup(buffer);
		type_of_token(tokens, *token_index - 1);
	}
	tokens[*token_index].value = NULL;
}

static void	handle_quote_char(t_process_input_data *data, int *i)
{
	char	quote_char;

	quote_char = data->input[*i];
	if (find_quote_to_the_end(data->buffer, &data->buffer_index, \
		data->input, i) == FALSE)
	{
		read_input_until_finding_the_quote(quote_char, data->buffer, \
				&data->buffer_index, data);
	}
}

static void	handle_operator_char(t_process_input_data *data, int *i)
{
	buffer_to_token_value(data->buffer, &data->buffer_index, data->tokens, \
			data->token_index);
	handle_operator(data->input, *i, data->tokens, data->token_index);
}

void	process_input(const char *input, t_token *tokens, int *token_index)
{
	t_process_input_data	data;
	int						i;

	fill_data(&data, input, tokens, token_index);
	i = -1;
	while (data.input[++i] != '\0')
	{
		if (is_quote_char(data.input[i]))
		{
			handle_quote_char(&data, &i);
			if (data.input[i] == '\0')
				return ;
		}
		else if (is_unexpected_parameter(data.input[i]))
		{
			printf("minishell: unexpected parameter: %c\n", data.input[i]);
			return ;
		}
		else if (is_operator(data.input[i]))
			handle_operator_char(&data, &i);
		else
			data.buffer[data.buffer_index++] = data.input[i];
	}
	handle_remaining_buffer(data.buffer, data.buffer_index, data.tokens, \
			data.token_index);
}
