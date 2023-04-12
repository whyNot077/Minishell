/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:16:53 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/12 12:17:13 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_stack(stack *list)
{
	stack_node	*dummy;

	if (list == NULL || list->top == NULL)
	{
		printf("empty list\n");
		return ;
	}
	dummy = list->headnode;
	printf("\n----------------\n");
	printf("\ndisplay_list\n");
	while (dummy != NULL)
	{
		printf("%d ", dummy->data);
		dummy = dummy->next;
	}
	printf("\n----------------\n");
}

void	display_list(t_array *list)
{
	size_t	i;

	i = 0;
	if (!list)
	{
		printf("no list\n");
		return ;
	}
	printf("list : ");
	while (i < list->current_count)
	{
		printf("%s ", get_token(list, i)->value);
		i++;
	}
	printf("\n");
}