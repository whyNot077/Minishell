/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:09:55 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/07 16:11:56 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	apply_pipe_output(t_execute *exe_tool)
{
	if (exe_tool->pipe_flag == TRUE)
	{
		dup2(exe_tool->pipe_fd[1], STDOUT_FILENO);
		close(exe_tool->pipe_fd[1]);
	}
}
