/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_str_in_the_valule.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:40:53 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/08 13:25:39 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*replace_substr(char *value, int start, int end,
		int replacement_value)
{
	char	*head;
	char	*tail;
	char	*replace_str;
	char	*tmp;
	char	*new_value;

	head = ft_substr(value, 0, start);
	tail = ft_substr(value, end, ft_strlen(value) - end);
	replace_str = ft_itoa(replacement_value);
	tmp = ft_strjoin(head, replace_str);
	free(head);
	free(replace_str);
	new_value = ft_strjoin(tmp, tail);
	free(tmp);
	free(tail);
	return (new_value);
}

static int	is_ifs_char(char ifs)
{
	return (ifs == '\0' || ifs == '$' || is_space(ifs));
}

char	*is_str_in_the_value(char *value)
{
	int		i;
	int		replacement_value;
	char	*new_value;

	i = 0;
	replacement_value = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			if (value[i] == '?')
			{
				if (is_ifs_char(value[i + 1]))
					replacement_value = g_exit_code;
				else
					continue ;
			}
			else if (value[i] == '$')
			{
				if (is_ifs_char(value[i + 1]))
					replacement_value = getpid();
				else
					continue ;
			}
			else
			{
				continue ;
			}
			new_value = replace_substr(value, i - 1, i + 1, replacement_value);
			free(value);
			return (new_value);
		}
		i++;
	}
	return (value);
}
