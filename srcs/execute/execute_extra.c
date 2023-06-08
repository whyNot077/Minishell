/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:18:03 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/08 20:38:22 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_exceptions(t_tree_node *root, t_execute *exe_tool)
{
	if (exe_tool->open_error == TRUE)
		infile_error(root, exe_tool);
	if (root->type == PIPE && root->right != NULL)
	{
		exe_tool->prev_fd = exe_tool->pipe_fd[0];
		close(exe_tool->pipe_fd[1]);
		exe_tool->curr_pipe_flag = FALSE;
	}
}
