/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:53:11 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 14:02:06 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURE_H
# define DATA_STRUCTURE_H

// dynamic array
t_array			*create_list(size_t max_num);
t_token			*get_token(t_array *list, size_t index);
int				is_full(t_array *list);
int				insert_token(t_array *list, char *value);
void			display_list(t_array *list);
void			destroy_list(t_array **list);

// binary tree
t_binarytree	*create_tree(void);
t_tree_node		*create_new_node(t_token *token);
void			destroy_tree(t_binarytree **tree);
void			free_tree_nodes(t_tree_node *node);

// display
void			display_tree(t_tree_node *node);

#endif