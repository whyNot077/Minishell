/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:08:59 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/07 12:29:58 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_array	*create_list(size_t max_num)
{
	t_array	*list;

	list = (t_array *)malloc(sizeof(t_array));
	if (!list)
	{
		perror("malloc error");
		exit(1);
	}
	list->max_count = max_num;
	list->token_count = 0;
	list->token = ft_calloc(max_num, sizeof(t_token));
	if (!list->token)
	{
		free(list);
		list = NULL;
		perror("malloc error");
		exit(1);
	}
	return (list);
}

t_token	*get_token(t_array *list, size_t index)
{
	if (!list || index < 0 || list->token_count < index)
		return (NULL);
	return (&list->token[index]);
}

int	is_full(t_array *list)
{
	return (list->token_count >= list->max_count);
}

int	insert_token(t_array *list, char *value)
{
	size_t	current;
	t_token	*dummy;
	t_token	new_token;

	if (!list || !value)
		return (ERROR);
	current = list->token_count;
	if (is_full(list))
	{
		dummy = list->token;
		list->token = ft_calloc(list->max_count * 1.5, sizeof(t_token));
		if (!list->token)
		{
			perror("malloc error");
			exit(1);
		}
		ft_memcpy(list->token, dummy, sizeof(t_token) * list->max_count);
		list->max_count *= 1.5;
		free(dummy);
	}
	new_token.value = value;
	new_token.type = type_of_token(new_token.value);
	list->token[current] = new_token;
	list->token_count++;
	return (1);
}

void	destroy_list(t_array **list)
{
	if (!*list)
		return ;
	if ((*list)->token != NULL)
	{
		free_tokens(&((*list)->token));
		(*list)->token = NULL;
	}
	free(*list);
	*list = NULL;
}
