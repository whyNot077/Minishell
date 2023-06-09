/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:27:02 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/09 12:41:40 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_exit_code(t_execute *exe_tool)
{
	int	pid;
	int	status;

	while (exe_tool->num_of_executed_commands)
	{
		pid = waitpid(-1, &status, 0);
		if (exe_tool->last_pid == pid)
		{
			g_exit_code = WEXITSTATUS(status);
			return ;
		}
		exe_tool->num_of_executed_commands--;
	}
}

void	apply_and(t_execute *exe_tool)
{
	check_exit_code(exe_tool);
	if ((exe_tool->open_error == FALSE) && g_exit_code == 0)
	{
		init_exe_tool(exe_tool);
	}
	else
		exe_tool->stop = TRUE;
}

void	apply_or(t_execute *exe_tool)
{
	int	num_commands;

	num_commands = exe_tool->num_of_executed_commands;
	check_exit_code(exe_tool);
	if ((exe_tool->open_error_for_and_or == FALSE \
		&& num_commands == 0) || g_exit_code == 0)
	{
		exe_tool->stop = TRUE;
	}
	else
	{
		init_exe_tool(exe_tool);
	}
}
