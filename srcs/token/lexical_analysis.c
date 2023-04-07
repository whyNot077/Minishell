/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:55:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/07 22:03:40 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_buffer(char *buffer, int *buffer_index, t_token *tokens,
		int *token_index)
{
	if (*buffer_index > 0)
	{
		buffer[*buffer_index] = '\0';
		tokens[(*token_index)++].value = ft_strdup(buffer);
		*buffer_index = 0;
	}
}

static void	handle_operator(const char *input, int i, t_token *tokens,
		int *token_index)
{
	char	operator_str[2];

	if (!is_space(input[i]))
	{
		operator_str[0] = input[i];
		operator_str[1] = '\0';
		tokens[(*token_index)++].value = ft_strdup(operator_str);
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
}

t_token	*create_tokens_by_lexical_analysis(const char *input)
{
	t_token	*tokens;
	char	buffer[MAX_INPUT_SIZE];
	int		buffer_index;
	int		token_index;
	int		i;

	tokens = ft_calloc(MAX_TOKENS, sizeof(t_token));
	if (tokens == NULL)
		error_exit("malloc error");
	buffer_index = 0;
	token_index = 0;
	i = -1;
	while (input[++i] != '\0')
	{
		if (is_operator(input[i]))
		{
			handle_buffer(buffer, &buffer_index, tokens, &token_index);
			handle_operator(input, i, tokens, &token_index);
			type_of_token(tokens, token_index - 1);
		}
		else
			buffer[buffer_index++] = input[i];
	}
	handle_remaining_buffer(buffer, buffer_index, tokens, &token_index);
	tokens[token_index].value = NULL;
	tokens = special_tokens(tokens, token_index);
	return (tokens);
}
