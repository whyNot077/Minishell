/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_str_in_the_valule.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:40:53 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/08 16:05:12 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*replace_substr(char *value, int start, int end, char *replace_str)
{
	char	*head;
	char	*tail;
	char	*tmp;
	char	*new_value;

	head = ft_substr(value, 0, start);
	tail = ft_substr(value, end, ft_strlen(value) - end);
	tmp = ft_strjoin(head, replace_str);
	free(head);
	new_value = ft_strjoin(tmp, tail);
	free(tmp);
	free(tail);
	return (new_value);
}

static char	*replace_value_and_free_old(char *value, int start, int end,
		char *replacement_value)
{
	char	*new_value;

	new_value = replace_substr(value, start, end, replacement_value);
	free(replacement_value);
	free(value);
	return (new_value);
}

static char	*handle_special_variables(char *value, int *i)
{
	char	*replacement_value;

	if (value[*i] == '?')
	{
		replacement_value = ft_itoa(g_exit_code);
		return (replace_value_and_free_old(value, *i - 1, *i + 1, \
				replacement_value));
	}
	return (NULL);
}

char	*is_str_in_the_value(char *value)
{
	int		i;
	char	*new_value;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			new_value = handle_special_variables(value, &i);
			if (new_value != NULL)
				return (new_value);
		}
		i++;
	}
	return (value);
}
