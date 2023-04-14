/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:26:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 21:54:53 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

// requirements
// structure -> built_in_flag
// structure -> pipe_flag

#include "arraylist.h"

void	execute(char **args, char **envp, int outfile_fd);
void	envp_init(t_execute *execute, char **envp);

#endif