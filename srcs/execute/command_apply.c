/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_apply.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:15:13 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/09 12:23:38 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_fork_error(void)
{
	ft_putstr_fd("minishell: fork error\n", STDERR_FILENO);
	exit(1);
}

int	validate_commands(char **args, char **full_path, \
								t_execute *exe_tool)
{
	int		paths_idx;
	char	*temp_path;

	if (exe_tool->paths == NULL)
		return (ERROR);
	paths_idx = 0;
	while (exe_tool->paths[paths_idx])
	{
		temp_path = ft_strjoin(exe_tool->paths[paths_idx], "/");
		*full_path = ft_strjoin(temp_path, args[0]);
		if (access(*full_path, X_OK) == 0)
		{
			free(temp_path);
			return (SUCCESS);
		}
		free(*full_path);
		free(temp_path);
		paths_idx++;
	}
	return (ERROR);
}

void	execute_command(char *full_path, char **args, t_execute *exe_tool)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		print_fork_error();
	exe_tool->last_pid = pid;
	if (pid == 0)
	{
		child_process(full_path, args, exe_tool);
	}
	else
	{
		parent_process(exe_tool);
		exe_tool->curr_pipe_flag = FALSE;
		free(full_path);
		if (exe_tool->outfile_fd > 0)
		{
			dup2(exe_tool->dup_tmp, STDOUT_FILENO);
			close(exe_tool->outfile_fd);
		}
	}
	restore_redirect_in(exe_tool);
	restore_redirect_out(exe_tool);
}
