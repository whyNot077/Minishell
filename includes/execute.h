/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:26:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/06 19:15:48 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

// requirements
// structure -> built_in_flag
// structure -> pipe_flag

enum e_sign
{
	EXIST = 1,
	NOT_EXIST = -1
};

void	execute(void);

#endif