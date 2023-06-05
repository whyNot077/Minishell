/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:16:28 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/05 19:27:46 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	here_doc_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		close(STDIN_FILENO);
		g_exit_code = 130;
	}
}

void	exec_parent_signal(struct sigaction sa)
{
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

// static void	child_signal(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 	}
// 	else if (sig == SIGQUIT)
// 	{
// 	}
// }

void	exec_child_signal(struct sigaction sa)
{
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	(void)sa;
	// sa.sa_handler = child_signal;
	// if (sigaction(SIGINT, &sa, NULL) == -1)
	// {
	// 	perror("sigaction");
	// 	exit(EXIT_FAILURE);
	// }
	// if (sigaction(SIGQUIT, &sa, NULL) == -1)
	// {
	// 	perror("sigaction");
	// 	exit(EXIT_FAILURE);
	// }
}

void	exec_heredoc_signal(struct sigaction sa)
{
	sa.sa_handler = here_doc_signal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}
