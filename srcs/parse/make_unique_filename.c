/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_unique_filename.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:42:09 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/31 17:42:58 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_exists(const char *filename)
{
	return (access(filename, F_OK) != -1);
}

char	*get_new_filename(const char *base, int index)
{
	char	*filename;
	char	*index_str;
	char	*underscore;
	char	*base_index;

	index_str = ft_itoa(index);
	underscore = ft_strdup("_");
	base_index = ft_strjoin(base, underscore);
	filename = ft_strjoin(base_index, index_str);
	free(base_index);
	free(underscore);
	free(index_str);
	return (filename);
}

char	*make_unique_filename(const char *previous_filename)
{
	int		index;
	char	*filename;

	index = 0;
	filename = NULL;
	while (1)
	{
		filename = get_new_filename(previous_filename, index);
		if (!file_exists(filename))
		{
			return (filename);
		}
		index++;
		free(filename);
	}
}
