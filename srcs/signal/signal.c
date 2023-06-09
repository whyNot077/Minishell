/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:33:16 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/09 11:19:05 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_signal(int flag)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (flag == PARENT_SIG)
	{
		exec_parent_signal(sa);
	}
	else if (flag == CHILD_SIG)
	{
		exec_child_signal(sa);
	}
	else if (flag == HEREDOE_SIG)
	{
		exec_heredoc_signal(sa);
	}
	else
	{
		exec_readline_signal(sa);
	}
}

static void	get_signal_from_child(int status)
{
	g_exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_exit_code = 128 + status;
	if (WTERMSIG(status) == SIGINT)
		printf("\n");
	else if (WTERMSIG(status) == SIGQUIT)
		printf("Quit: 3\n");
}

int	get_pid_and_signal(t_execute *exe_tool)
{
	int	pid;
	int	status;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (exe_tool->last_pid == pid)
			get_signal_from_child(status);
		else if (pid == -1)
			return (1);
	}
}
