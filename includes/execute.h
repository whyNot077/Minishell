/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:26:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/28 21:00:58 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

// requirements
// structure -> built_in_flag
// structure -> pipe_flag

void		execute(t_binarytree *tree, t_execute *exe_tool);
t_execute	*envp_init(char **envp);
void		free_envp(t_execute *execute);

#endif