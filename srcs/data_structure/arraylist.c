/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:29:20 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/13 20:10:51 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_arraylist *al_init(void)
{
	t_arraylist *list;
	
	list = malloc(sizeof(t_arraylist));
	list->capacity = 1;
	list->size = 0;
	list->data = malloc(sizeof(char *) * list->capacity);
	return (list);
}

char	*al_get(t_arraylist *list, int index)
{
	if (index >= list->size || index < 0)
		return (NULL);
	return (list->data[index]);
}

void	al_add_rear(t_arraylist *list, char *element)
{
	char	**temp;

	if (list->size == list->capacity)
	{
		list->capacity *= 2;
		temp = list->data;
		list->data = malloc(sizeof(char *) * list->capacity);
		if (list->data == NULL)
			return ;
		ft_memcpy(list->data, temp, sizeof(char *) * list->size);
		free(temp);
		temp = NULL;
	}
	list->data[list->size++] = element;
}

void	al_remove(t_arraylist *list, int index)
{
	int		i;

	if (index >= list->size || index < 0)
		return ;
	i = index;
	while (i < list->size - 1)
	{
		list->data[i] = list->data[i + 1];
		i++;
	}
	list->size--;
}
