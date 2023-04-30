/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:59:54 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/30 19:24:07 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	create_pipe(int *fd)
{
	if (pipe(fd) < 0)
	{
		perror("ERROR: Failed to create a pipe\n");
		exit(EXIT_FAILURE);
	}
	if (fd[0] < 0 || fd[1] < 0)
	{
		perror("ERROR: Failed to create a pipe\n");
		exit(EXIT_FAILURE);
	}
}

void	pipe_apply(t_binarytree *tree, t_execute *exe_tool)
{
	create_pipe(exe_tool->pipe_fd);
	exe_tool->pid = fork();
}
