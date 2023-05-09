/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_apply.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:47:00 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/08 20:58:27 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	apply_redirect_in(t_execute *exe_tool)
{
	if (exe_tool->infile_fd > 0)
	{
		exe_tool->dup_tmp = dup(STDIN_FILENO);
		dup2(exe_tool->infile_fd, STDIN_FILENO);
	}
}

void	apply_redirect_out(t_execute *exe_tool)
{
	if (exe_tool->outfile_fd > 0)
	{
		exe_tool->dup_tmp = dup(STDOUT_FILENO);
		dup2(exe_tool->outfile_fd, STDOUT_FILENO);
	}
}

void	restore_redirect_in(t_execute *exe_tool)
{
	if (exe_tool->infile_fd > 0)
	{
		dup2(exe_tool->dup_tmp, STDIN_FILENO);
		close(exe_tool->infile_fd);
		exe_tool->infile_fd = 0;
	}
}

void	restore_redirect_out(t_execute *exe_tool)
{
	if (exe_tool->outfile_fd > 0)
	{
		dup2(exe_tool->dup_tmp, STDOUT_FILENO);
		close(exe_tool->outfile_fd);
		exe_tool->outfile_fd = 0;
	}
}
