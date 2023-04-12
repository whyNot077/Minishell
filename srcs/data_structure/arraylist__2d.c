/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist__2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:29:20 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/12 10:54:52 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	al_init(t_arraylist *list)
{
	list->size = 0;
	list->capacity = INITIAL_CAPACITY;
	list->data = malloc(sizeof(char *) * list->capacity);
	if (list->data == NULL)
		return ;
	list->data[list->capacity] = NULL;
}

char	*al_get(t_arraylist *list, int row, int col)
{
	if (row >= list->size || col >= ft_strlen(list->data[row]))
		return (NULL);
}