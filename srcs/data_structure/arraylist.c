/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:29:20 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/26 17:07:15 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arraylist *al_init(void)
{
	t_arraylist *list;
	
	list = malloc(sizeof(t_arraylist));
	list->size = 1;
	list->count = 0;
	list->data = malloc(sizeof(char *) * list->size);
	list->data[list->count] = NULL;
	return (list);
}

char	*al_get(t_arraylist *list, int index)
{
	if (index >= list->count || index < 0)
		return (NULL);
	return (list->data[index]);
}

void	al_add_rear(t_arraylist *list, char *element)
{
	char	**temp;

	if (list->count >= list->size)
	{
		list->size *= 2;
		temp = list->data;
		list->data = malloc(sizeof(char *) * (list->size + 1));
		if (list->data == NULL)
			return ;
		ft_memcpy(list->data, temp, sizeof(char *) * list->count);
		free(temp);
		temp = NULL;
	}
	list->data[list->count++] = element;
	list->data[list->count] = NULL;
}

void	al_remove(t_arraylist *list, int index)
{
	int		i;

	if (index >= list->count || index < 0)
		return ;
	free(list->data[index]);
	i = index;
	while (i < list->count - 1)
	{
		list->data[i] = list->data[i + 1];
		i++;
	}
	list->count--;
	list->data[list->count] = NULL;
}
