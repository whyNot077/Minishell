/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_apply.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:55:45 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/05 18:40:57 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_commands(char **args, char **full_path, \
								t_execute *exe_tool)
{
	int		paths_idx;
	char	*temp_path;

	if (access(args[0], X_OK) == 0)
	{
		*full_path = ft_strdup(args[0]);
		return (SUCCESS);
	}
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
	int		status;

	pid = fork();
	if (pid == 0)
		execve(full_path, args, NULL);
	else
	{
		waitpid(pid, &status, 0);
		free(full_path);
		if (exe_tool->outfile_fd > 0)
		{
			dup2(exe_tool->dup_tmp, STDOUT_FILENO);
			close(exe_tool->outfile_fd);
		}
	}
}

void	apply_command(char **args, t_execute *exe_tool)
{
	char	*full_path;

	full_path = NULL;
	if (validate_commands(args, &full_path, exe_tool) == ERROR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": commands not found\n", STDERR_FILENO);
		return ;
	}
	execute_command(full_path, args, exe_tool);
}
