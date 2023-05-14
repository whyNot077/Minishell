/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:06:14 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/14 16:18:22 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process(char *full_path, char **args, t_execute *exe_tool)
{
	printf("child_process\n");
	printf("prev_fd: %d\n", exe_tool->prev_fd);
	if (exe_tool->prev_fd > 0)
	{
		dup2(exe_tool->prev_fd, STDIN_FILENO);
		printf("prev_fd: %d\n", exe_tool->prev_fd);
		close(exe_tool->prev_fd);
	}
	if (exe_tool->pipe_flag == TRUE && exe_tool->outfile_fd == 0)
	{
		dup2(exe_tool->pipe_fd[1], STDOUT_FILENO);
		close(exe_tool->pipe_fd[1]);
	}
	if (exe_tool->built_in_flag == FALSE)
		apply_redirect_in(exe_tool);
	apply_redirect_out(exe_tool);
	exe_tool->built_in_flag = FALSE;
	execve(full_path, args, exe_tool->env->data);
	exit(1);
}
