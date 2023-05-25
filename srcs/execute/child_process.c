/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:06:14 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/25 19:26:09 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	child_process(char *full_path, char **args, t_execute *exe_tool)
{
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
	if (exe_tool->built_in_flag == FALSE)
		apply_redirect_in(exe_tool);
	apply_redirect_out(exe_tool);
	exe_tool->built_in_flag = FALSE;
	if (exe_tool->pipe_fd[0] > 0)
		close(exe_tool->pipe_fd[0]);
	execve(full_path, args, exe_tool->env->data);
	print_error("minishell: ");
	print_error(args[0]);
	print_error(": ");
	print_error("command not found\n");
	exit(1);
}
