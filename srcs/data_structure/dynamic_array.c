/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:08:59 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/12 12:18:59 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_array	*create_list(size_t max_num)
{
	t_array	*list;

	list = (t_array *)malloc(sizeof(t_array));
	if (!list)
		return (NULL);
	list->max_count = max_num;
	list->current_count = 0;
	list->token = ft_calloc(max_num, sizeof(t_token));
	if (!list->token)
	{
		free(list);
		list = NULL;
		return (NULL);
	}
	return (list);
}

t_token	*get_token(t_array *list, size_t index)
{
	if (!list || index < 0 || list->current_count < index)
		return (NULL);
	return (list->token + index);
}

int is_full(t_array *list)
{
	return (list->current_count >= list->max_count);
}

int	insert_token(t_array *list, t_token new_token, size_t index)
{
	size_t	current;
	t_token	*dummy;

	current = list->current_count;
	if (!list || index < 0 || current < index)
		return (0);
	if (is_full(list))
	{
		dummy = list->token;
		list->token = ft_calloc(list->max_count * 1.5, sizeof(t_token));
		if (!list->token)
			error_exit("malloc error");
		ft_memcpy(list->token, dummy, sizeof(t_token) * list->max_count);
		list->max_count *= 1.5;
		free(dummy);
	}
	while (index < current)
	{
		*get_token(list, current) = *get_token(list, current - 1);
		current--;
	}
	*get_token(list, index) = new_token;
	list->current_count++;
	return (1);
}

int	remove_token(t_array *list, size_t index)
{
	size_t i;

	i = (list->max_count) - 1;
	if (index < 0 || ((list->current_count) <= index))
		return (0);
	while (index < i)
	{
		*get_token(list, index) = *get_token(list, index + 1);
		index++;
	}
	(*get_token(list, index)).value = NULL;
	list->current_count--;
	return (1);
}

void	destroy_list(t_array **list)
{
	if (!*list)
		return ;
	if ((*list)->token != NULL)
	{
		free((*list)->token);
		(*list)->token = NULL;
	}
	free(*list);
	*list = NULL;
}