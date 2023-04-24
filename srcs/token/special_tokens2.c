/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:13:45 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/24 19:03:30 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_special_token(char *token)
{
	if (token == NULL)
		return (ERROR);
	return (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, "<", 1) == 0 \
		|| ft_strncmp(token, "&", 1) == 0 || ft_strncmp(token, "|", 1) == 0);
}

void	num_of_special_tokens_and_space(t_token *tokens, \
		int token_number, int *count, int *space)
{
	int	i;

	i = -1;
	(*count) = 0;
	while (++i < token_number - 1)
	{
		if (is_special_token(tokens[i].value))
			if (++i < token_number && is_special_token(tokens[i].value))
				if (tokens[i - 1].type == tokens[i].type)
					(*count)++;
		if (is_space_token(tokens[i].value))
			(*space)++;
	}
}

void	fill_data(t_process_input_data *data, const char *input, \
		t_array *list)
{
	data->input = input;
	data->list = list;
	data->tokens = list->token;
	data->buffer_index = 0;
}

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '&' || c == '|');
}
