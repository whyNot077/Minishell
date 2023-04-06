/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:38:45 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/06 15:28:25 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	destroy_list(list **linked_list)
{
	node *dummy;
	node *remove;

	if (!*linked_list)
		return ;	
	dummy = (*linked_list)->headnode;
	while (dummy)
	{
		remove = dummy;
		dummy = dummy->next;
		free(remove);
		remove = NULL;
	}
	free(*linked_list);
	*linked_list = NULL;
	printf("destroy complete\n");
}