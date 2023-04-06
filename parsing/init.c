/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:01:27 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/06 15:03:13 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init(void)
{
	list *linked_list;

	linked_list = create_linkedlist();
	add_data(linked_list, "hahaha\n");
	add_data(linked_list, "hehehe\n");
	display_list(linked_list);
}