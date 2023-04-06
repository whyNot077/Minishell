/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:33 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/06 15:08:09 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

list	*create_linkedlist(void)
{
	list *linked_list;
	linked_list = calloc(1, sizeof(list));
	if (linked_list == NULL)
		return (NULL);
	return (linked_list);
}


node	*create_new_node(char *data)
{
	node	*new_node;
	
	new_node = calloc(1, sizeof(node));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	return (new_node);
}

int	get_the_index_of_the_string(list *linked_list, char *to_find)
{
	int		index;
	node	*dummy;

	index = 0;
	if (linked_list == NULL || linked_list->headnode == NULL)
		return (-1);
	dummy = linked_list->headnode;
	while (dummy && dummy->next)
	{
		if (dummy->data == to_find)
			return (index);
		dummy = dummy->next;
		index++;
	}
	return (-1);
}

node	*get_node_by_the_index(list *linked_list, int index)
{
	int 	i;
	node	*dummy;

	i = 0;
	if (linked_list == NULL)
		return (NULL);
	dummy = linked_list->headnode;
	while ((i < index) && dummy && dummy->next)
	{
		dummy = dummy->next;
		i++;
	}
	if (i == index)
		return (dummy);
	return (NULL);
}

int		insert_data_to_the_index(list *linked_list, int index, char *data)
{
	node	*before_node;
	node	*new_node;

	if (linked_list == NULL)
		return (0);
	new_node = create_new_node(data);
	if (new_node == NULL)
		return (0);
	if (index == 0)
	{
		new_node->next = linked_list->headnode;
		linked_list->headnode = new_node;
		return (1);
	}
	before_node = get_node_by_the_index(linked_list, index - 1);
	if (before_node == NULL)
		return (0);
	new_node->next = before_node->next;
	before_node->next = new_node;
	return (1);
}

int		add_data(list *linked_list, char *data)
{
	node	*dummy;
	node	*new_node;

	if (linked_list == NULL)
		return (0);
	dummy = linked_list->headnode;
	new_node = create_new_node(data);
	if (dummy == NULL)
	{
		linked_list->headnode = new_node;
		return (1);
	}
	if (new_node == NULL)
		return (0);
	while (dummy && dummy->next)
		dummy = dummy->next;
	dummy->next = new_node;
	return (1);
}

int		remove_node(list *linked_list, int index)
{
	node *before_node;
	node *remove_node;

	if (index == 0)
	{
		remove_node = linked_list->headnode;
		linked_list->headnode = remove_node->next;
		free(remove_node);
		return (1);
	}
	before_node = get_node_by_the_index(linked_list, index - 1);
	if (before_node == NULL)
		return (0);
	remove_node = before_node->next;
	if (remove_node == NULL)
		return (0);
	before_node->next = remove_node->next;
	free(remove_node);
	return (1);
}

void	display_list(list *linked_list)
{
	node	*dummy;
	int		index;

	index = 0;
	if (!linked_list || !linked_list->headnode)
	{
		printf("no list\n");
		return ;
	}
	dummy = linked_list->headnode;
	printf("\ndisplay_list\n");
	while (dummy)
	{
		printf("[%d] %s ", index++, dummy->data);
		dummy = dummy->next;
	}
	printf("\n");
}
