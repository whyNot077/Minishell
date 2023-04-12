/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:55:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/12 18:15:54 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	duplicate_token_value(t_array *list, t_token *tokens, size_t *i,
		size_t *j)
{
	if (tokens[*j].value != NULL)
		insert_token(list, ft_strdup(tokens[*j].value));
	else
		insert_token(list, NULL);
	(*i)++;
	(*j)++;
}

static void	join_token_values(t_array *list, t_token *tokens, \
	size_t *i, size_t *j)
{
	insert_token(list, ft_strjoin(tokens[*j].value, tokens[*j + 1].value));
	(*j) += 2;
	(*i)++;
}

static t_array	*copy_tokens(t_array *list, t_token *tokens, size_t token_index,
		size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < token_index - count && j < token_index)
	{
		if (is_special_token(tokens[j].value))
		{
			if (j + 1 < token_index && is_special_token(tokens[j + 1].value)
				&& tokens[j].type == tokens[j + 1].type)
				join_token_values(list, tokens, &i, &j);
			else if (!is_space_token(tokens[j].value))
				duplicate_token_value(list, tokens, &i, &j);
		}
		else if (!is_space_token(tokens[j].value))
			duplicate_token_value(list, tokens, &i, &j);
		else
			j++;
	}
	if (i < list->max_count)
	{
		list->token[i].value = NULL;
	}
	return (list);
}

t_array	*special_tokens(t_array *list)
{
	int		count;
	int		space;
	t_array	*new_list;

	count = 0;
	space = 0;
	num_of_special_tokens_and_space(list->token, list->token_count, &count, \
			&space);
	if (count == 0 && space == 0)
		return (list);
	new_list = create_list(list->token_count - count - space + 1);
	if (new_list == NULL)
		error_exit("malloc failed");
	new_list = copy_tokens(new_list, list->token, list->token_count, \
			count + space);
	destroy_list(&list);
	return (new_list);
}
