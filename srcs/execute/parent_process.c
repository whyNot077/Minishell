/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:41:19 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/25 19:26:09 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(t_execute *exe_tool)
{
	if (exe_tool->prev_fd > 0)
		close(exe_tool->prev_fd);
	if (exe_tool->curr_pipe_flag == TRUE)
	{
		close(exe_tool->pipe_fd[1]);
		exe_tool->prev_fd = exe_tool->pipe_fd[0];
	}
}
