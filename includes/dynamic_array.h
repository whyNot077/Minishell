/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:14:46 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/12 12:16:26 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

t_array	*create_list(size_t max_num);
t_token	*get_token(t_array *list, size_t index);
int		is_full(t_array *list);
int		insert_token(t_array *list, t_token new_node, size_t index);
int		remove_token(t_array *list, size_t index);
void	display_list(t_array *list);
void	destroy_list(t_array **list);

#endif