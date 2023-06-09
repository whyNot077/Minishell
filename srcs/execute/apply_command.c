/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:58:55 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/09 11:59:53 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_paths(t_execute *exe_tool)
{
	int		i;

	i = 0;
	while (exe_tool->paths[i])
		free(exe_tool->paths[i++]);
	free(exe_tool->paths);
	exe_tool->paths = NULL;
}

void	apply_command(char **args, t_execute *exe_tool)
{
	char	*full_path;

	exec_signal(PARENT_SIG);
	full_path = NULL;
	if (access(args[0], X_OK) == 0)
	{
		full_path = ft_strdup(args[0]);
		exe_tool->num_of_executed_commands++;
		execute_command(full_path, args, exe_tool);
		return ;
	}
	else
	{
		exe_tool->execute_error = TRUE;
	}
	if (get_env_value("PATH", exe_tool->env) == SUCCESS)
	{
		exe_tool->paths = get_paths(exe_tool->env->data);
		if (validate_commands(args, &full_path, exe_tool) == ERROR)
		{
			exe_tool->execute_error = TRUE;
			full_path = NULL;
		}
		free_paths(exe_tool);
	}
	else
	{
		exe_tool->execute_error = TRUE;
	}
	exe_tool->num_of_executed_commands++;
	execute_command(full_path, args, exe_tool);
	g_exit_code = 0;
}
