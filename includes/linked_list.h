/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:22:34 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/06 15:46:31 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

typedef struct node {
	char		*data;
	struct node	*next;
} node;

typedef struct list {
	node	*headnode;
} list;

list	*create_linkedlist(void);
node	*create_new_node(char *data);
int		get_the_index_of_the_string(list *linked_list, char *to_find);
node	*get_node_by_the_index(list *linked_list, int index);
int		insert_data_to_the_index(list *linked_list, int index, char *data);
int		add_data(list *linked_list, char *data);
int		remove_node(list *linked_list, int index);
void	display_list(list *linked_list);
void	destroy_list(list **linked_list);

#endif