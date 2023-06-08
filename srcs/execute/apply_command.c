/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:58:55 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/08 18:04:22 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_accessiable_command(char **args, t_execute *exe_tool, char **full_path, int *path_value)
{
	if (access(args[0], X_OK) == 0)
	{
		*full_path = ft_strdup(args[0]);
		execute_command(*full_path, args, exe_tool);
		return (ERROR);
	}
	*path_value = get_env_value("PATH", exe_tool->env);
	if (*path_value == ERROR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_exit_code = 127;
		return (ERROR);
	}
	return (SUCCESS);
}

static void	free_paths(t_execute *exe_tool)
{
	int		i;

	i = 0;
	while (exe_tool->paths[i])
		free(exe_tool->paths[i++]);
	free(exe_tool->paths);
	exe_tool->paths = NULL;
}

static void free_and_close(t_execute *exe_tool)
{
	free_paths(exe_tool);
	if (exe_tool->outfile_fd > 0)
		close(exe_tool->outfile_fd);
	if (exe_tool->curr_pipe_flag == TRUE)
		close(exe_tool->pipe_fd[1]);
}

static void	is_invalid_command(char **args, t_execute *exe_tool)
{
	if (exe_tool->open_error == FALSE)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		g_exit_code = 127;
		exe_tool->execute_error = TRUE;
	}
	if (exe_tool->prev_fd > 0)
		close(exe_tool->prev_fd);
	free_and_close(exe_tool);
}

void	apply_command(char **args, t_execute *exe_tool)
{
	int		path_value;
	char	*full_path;

	full_path = NULL;
	path_value = 0;
	exec_signal(PARENT_SIG);
	if (is_accessiable_command(args, exe_tool, &full_path, &path_value) == ERROR)
		return ;
	exe_tool->paths = get_paths(exe_tool->env->data);
	if (validate_commands(args, &full_path, exe_tool) == ERROR)
	{
		return (is_invalid_command(args, exe_tool));
	}
	else
		exe_tool->execute_error = FALSE;
	if (exe_tool->execute_error == TRUE)
	{
		free_and_close(exe_tool);
		free(full_path);
		return ;
	}
	execute_command(full_path, args, exe_tool);
	g_exit_code = 0;
	free_paths(exe_tool);
}
