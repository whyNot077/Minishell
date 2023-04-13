/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:55:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 14:16:42 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	buffer_to_token_value(char *buffer, int *buffer_index, t_array *list)
{
	char	*new_value;

	if (*buffer_index > 0)
	{
		buffer[*buffer_index] = '\0';
		new_value = ft_strdup(buffer);
		insert_token(list, new_value);
		*buffer_index = 0;
	}
}

t_token	*create_tokens_by_lexical_analysis(const char *input)
{
	t_array	*list;
	t_token	*token;

	list = create_list(MAX_TOKENS);
	process_input(list, input);
	list = special_tokens(list);
	token = list->token;
	token->token_count = list->token_count;
	free(list);
	return (token);
}
