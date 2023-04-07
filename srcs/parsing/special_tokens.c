/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:55:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/07 20:51:48 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_special_token(char *token)
{
	if (token == NULL)
		return (ERROR);
	return (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, "<", 1) == 0\
		|| ft_strncmp(token, "&", 1) == 0 || ft_strncmp(token, "|", 1) == 0);
}

static int	num_of_special_tokens(t_token *tokens, int token_index)
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

static void	duplicate_token_value(t_token *new_tokens, t_token *tokens, int i,\
		int j)
{
	if (tokens[j].value != NULL)
	{
		new_tokens[i].value = ft_strdup(tokens[j].value);
		type_of_token(new_tokens, i);
	}
	else
	{
		new_tokens[i].value = NULL;
	}
}

static void	join_token_values(t_token *new_tokens, t_token *tokens, int i,\
		int *j)
{
	new_tokens[i].value = ft_strjoin(tokens[*j].value, tokens[*j + 1].value);
	type_of_token(new_tokens, i);
	(*j)++;
}

static t_token	*copy_tokens(t_token *tokens, t_token *new_tokens,\
		int token_index, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < token_index - count)
	{
		if (is_special_token(tokens[j].value))
		{
			if (j + 1 < token_index && is_special_token(tokens[j + 1].value)\
				&& tokens[j].type == tokens[j + 1].type)
				join_token_values(new_tokens, tokens, i, &j);
			else
				duplicate_token_value(new_tokens, tokens, i, j);
		}
		else
			duplicate_token_value(new_tokens, tokens, i, j);
		i++;
		j++;
	}
	new_tokens[i].value = NULL;
	return (new_tokens);
}

t_token	*special_tokens(t_token *tokens, int token_index)
{
	int count;
	t_token *new_tokens;

	count = num_of_special_tokens(tokens, token_index);
	if (count == 0)
		return (tokens);
	new_tokens = ft_calloc(token_index - count + 1, sizeof(t_token));
	if (new_tokens == NULL)
		error_exit("malloc failed");
	new_tokens = copy_tokens(tokens, new_tokens, token_index, count);
	free_tokens(tokens);
	return (new_tokens);
}