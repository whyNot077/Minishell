/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:41:19 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/10 18:03:02 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(t_execute *exe_tool)
{
	if (exe_tool->pipe_flag == TRUE)
	{
		dup2(exe_tool->dup_tmp, STDOUT_FILENO);
		close(exe_tool->pipe_fd[1]);
		close(exe_tool->dup_tmp);
		exe_tool->prev_fd = exe_tool->pipe_fd[0];
	}
}
