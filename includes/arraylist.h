/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:13:34 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/31 19:16:36 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYLIST_H
# define ARRAYLIST_H

# define MAX_STRING_LENGTH 100
# define INITIAL_CAPACITY 10

t_arraylist	*al_init(void);
char		*al_get(t_arraylist *list, int index);
void		al_add_rear(t_arraylist *list, char *element);
void		al_remove(t_arraylist *list, int index);

#endif