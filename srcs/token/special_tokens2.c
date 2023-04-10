/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:13:45 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/10 14:18:47 by minkim3          ###   ########.fr       */
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

int	num_of_special_tokens(t_token *tokens, int token_index)
{
	int	i;
	int	num_of_special_tokens;

	i = -1;
	num_of_special_tokens = 0;
	while (++i < token_index)
	{
		if (is_special_token(tokens[i].value))
			if (++i < token_index && is_special_token(tokens[i].value))
				if (tokens[i - 1].type == tokens[i].type)
					num_of_special_tokens++;
	}
	return (num_of_special_tokens);
}

int	is_unexpected_parameter(char c)
{
	return (c == '(' || c == ')' || c == '\\' || c == '^' || \
		c == '?' || c == '*' || c == '+' || c == ';');
}

void	fill_data(t_process_input_data *data, const char *input, \
		t_token *tokens, int *token_index)
{
	data->input = input;
	data->tokens = tokens;
	data->token_index = token_index;
	data->buffer_index = 0;
}
