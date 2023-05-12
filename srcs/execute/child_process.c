/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:06:14 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/11 19:51:15 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process(char *full_path, char **args, t_execute *exe_tool)
{
	if (exe_tool->prev_fd > 0 && exe_tool->infile_fd == 0)
	{
		dup2(exe_tool->prev_fd, STDIN_FILENO);
		close(exe_tool->prev_fd);
	}
	if (exe_tool->pipe_flag == TRUE && exe_tool->outfile_fd == 0)
	{
		dup2(exe_tool->pipe_fd[1], STDOUT_FILENO);
		close(exe_tool->pipe_fd[1]);
	}
	apply_redirect_in(exe_tool);
	apply_redirect_out(exe_tool);
	execve(full_path, args, exe_tool->env->data);
	exit(1);
}
