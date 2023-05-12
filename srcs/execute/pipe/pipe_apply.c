/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:09:55 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/11 19:37:30 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	apply_built_in_pipe(char **args, t_execute *exe_tool)
{
	pid_t	pid;
	int		status;

	printf("built_in_with_pipe\n");
	exe_tool->dup_tmp = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		close(exe_tool->pipe_fd[0]);
		dup2(exe_tool->pipe_fd[1], STDOUT_FILENO);
		close(exe_tool->pipe_fd[1]);
		built_in(args, exe_tool);
		exit(0);
	}
	else
	{
		close(exe_tool->pipe_fd[1]);
		dup2(exe_tool->dup_tmp, STDOUT_FILENO);
		close(exe_tool->dup_tmp);
		exe_tool->prev_fd = exe_tool->pipe_fd[0];
		waitpid(pid, &status, 0);
		exe_tool->pipe_flag = FALSE;
	}
}
