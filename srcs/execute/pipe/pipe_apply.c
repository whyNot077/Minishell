/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:09:55 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/08 17:38:54 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	built_in_child_process(t_execute *exe_tool, char **args)
{
	if (exe_tool->open_error == TRUE)
		exit(0);
	if (exe_tool->prev_fd > 0)
	{
		dup2(exe_tool->prev_fd, STDIN_FILENO);
		close(exe_tool->prev_fd);
	}
	if (exe_tool->curr_pipe_flag == TRUE && exe_tool->outfile_fd == 0)
	{
		dup2(exe_tool->pipe_fd[1], STDOUT_FILENO);
		close(exe_tool->pipe_fd[1]);
	}
	if (exe_tool->pipe_fd[0] > 0)
		close(exe_tool->pipe_fd[0]);
	built_in(args, exe_tool);
	exit(0);
}

void	apply_built_in_pipe(char **args, t_execute *exe_tool)
{
	pid_t	pid;
	int		status;

	exe_tool->built_in_flag = TRUE;
	exe_tool->dup_tmp = dup(STDOUT_FILENO);
	pid = fork();
	exe_tool->last_pid = pid;
	if (pid == 0)
		built_in_child_process(exe_tool, args);
	else
	{
		close(exe_tool->pipe_fd[1]);
		dup2(exe_tool->dup_tmp, STDOUT_FILENO);
		close(exe_tool->dup_tmp);
		exe_tool->prev_fd = exe_tool->pipe_fd[0];
		waitpid(pid, &status, 0);
		g_exit_code = WEXITSTATUS(status);
		exe_tool->curr_pipe_flag = FALSE;
	}
}
