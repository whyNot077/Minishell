/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:55:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/08 21:15:06 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	buffer_to_token_value(char *buffer, int *buffer_index,
		t_token *tokens, int *token_index)
{
	if (*buffer_index > 0)
	{
		buffer[*buffer_index] = '\0';
		tokens[(*token_index)++].value = ft_strdup(buffer);
		type_of_token(tokens, *token_index - 1);
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
}

static void	process_input(const char *input, t_token *tokens, int *token_index)
{
	char	buffer[MAX_INPUT_SIZE];
	int		buffer_index;
	char	quote_char;
	int		i;

	buffer_index = 0;
	i = -1;
	while (input[++i] != '\0')
	{
		if (is_quote_char(input[i]))
		{
			buffer_to_token_value(buffer, &buffer_index, tokens, token_index);
			quote_char = input[i];
			if (find_quote_to_the_end(buffer, &buffer_index, input, &i) == FALSE)
				read_input_until_finding_the_quote(quote_char, buffer, &buffer_index);
			buffer_to_token_value(buffer, &buffer_index, tokens, token_index);
			return ;
		}
		else if (is_operator(input[i]))
		{
			buffer_to_token_value(buffer, &buffer_index, tokens, token_index);
			handle_operator(input, i, tokens, token_index);
		}
		else
			buffer[buffer_index++] = input[i];
	}
	handle_remaining_buffer(buffer, buffer_index, tokens, token_index);
	tokens[*token_index].value = NULL;
}

t_token	*create_tokens_by_lexical_analysis(const char *input)
{
	t_token	*tokens;
	int		token_index;

	token_index = 0;
	tokens = ft_calloc(MAX_TOKENS, sizeof(t_token));
	if (tokens == NULL)
		error_exit("malloc error");
	process_input(input, tokens, &token_index);
	for (int i = 0; tokens[i].value != NULL; i++)
		printf("token[%d].value = %s\n", i, tokens[i].value);
	tokens = special_tokens(tokens, token_index);
	printf("\nafter special_tokens\n");
	for (int i = 0; tokens[i].value != NULL; i++)
		printf("token[%d].value = %s\n", i, tokens[i].value);
	return (tokens);
}
