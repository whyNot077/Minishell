/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_apply.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:15:13 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/08 14:36:46 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_fork_error(void)
{
	ft_putstr_fd("minishell: fork error\n", STDERR_FILENO);
	exit(1);
}

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

void	apply_command(char **args, t_execute *exe_tool)
{
	int		i;
	int 	path_value;
	char	*full_path;

	full_path = NULL;
	exec_signal(PARENT_SIG);
	if (access(args[0], X_OK) == 0)
	{
		full_path = ft_strdup(args[0]);
		execute_command(full_path, args, exe_tool);
		return ;
	}
	path_value = get_env_value("PATH", exe_tool->env);
	if (path_value == ERROR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_exit_code = 127;
		return ;
	}
	exe_tool->paths = get_paths(exe_tool->env->data);
	if (validate_commands(args, &full_path, exe_tool) == ERROR)
	{
		if (exe_tool->open_error == FALSE)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			g_exit_code = 127;
			exe_tool->execute_error = TRUE;
		}
		i = 0;
		while (exe_tool->paths[i])
			free(exe_tool->paths[i++]);
		free(exe_tool->paths);
		if (exe_tool->outfile_fd > 0)
			close(exe_tool->outfile_fd);
		if (exe_tool->curr_pipe_flag == TRUE)
			close(exe_tool->pipe_fd[1]);
		return ;
	}
	if (exe_tool->execute_error == TRUE)
	{
		i = 0;
		while (exe_tool->paths[i])
			free(exe_tool->paths[i++]);
		free(exe_tool->paths);
		if (exe_tool->outfile_fd > 0)
			close(exe_tool->outfile_fd);
		if (exe_tool->curr_pipe_flag == TRUE)
			close(exe_tool->pipe_fd[1]);
		return ;
	}
	execute_command(full_path, args, exe_tool);
	g_exit_code = 0;
	i = 0;
	while (exe_tool->paths[i])
		free(exe_tool->paths[i++]);
	free(exe_tool->paths);
	exe_tool->paths = NULL;
}
