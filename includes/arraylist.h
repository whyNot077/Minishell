/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:13:34 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/12 10:54:40 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYLIST_H
# define ARRAYLIST_H

# define MAX_STRING_LENGTH 100
# define INITIAL_CAPACITY 10

typedef struct s_arraylist
{
	int		size;
	int		capacity;
	char	**data;
}			t_arraylist;

#endif