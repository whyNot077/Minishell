/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:55:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/09 22:14:22 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	buffer_to_token_value(char *buffer, int *buffer_index,
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

t_token	*create_tokens_by_lexical_analysis(const char *input)
{
	t_token	*tokens;
	int		token_index;

	token_index = 0;
	tokens = ft_calloc(MAX_TOKENS, sizeof(t_token));
	if (tokens == NULL)
		error_exit("malloc error");
	process_input(input, tokens, &token_index);
	tokens = special_tokens(tokens, token_index);
	for (int i = 0; tokens[i].value; i++)
		printf("tokens[%d].value = %s\n", i, tokens[i].value);
	return (tokens);
}
