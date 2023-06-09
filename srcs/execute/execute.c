/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/09 12:26:59 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	apply_built_in(t_tree_node *root, t_execute *exe_tool)
{
	if ((root->type == BUILTIN && exe_tool->pipe_flag == FALSE \
			&& exe_tool->open_error == FALSE))
	{
		exe_tool->num_of_executed_commands++;
		built_in(root->command, exe_tool);
	}
	else if (root->type == BUILTIN && exe_tool->pipe_flag == TRUE)
	{
		if (exe_tool->curr_pipe_flag == FALSE)
		{
			exe_tool->pipe_flag = FALSE;
			exe_tool->exit_flag = TRUE;
		}
		exe_tool->num_of_executed_commands++;
		apply_built_in_pipe(root->command, exe_tool);
	}
}

void	infile_error(t_tree_node *root, t_execute *exe_tool)
{
	int	type;

	type = root->type;
	if ((type == PIPE && root->right != NULL) || type == BUILTIN || \
		type == WORD)
		exe_tool->open_error = FALSE;
}

void	execute(t_tree_node *root, t_execute *exe_tool)
{
	if (root == NULL)
		return ;
	execute(root->left, exe_tool);
	if (root->type == AND)
		apply_and(exe_tool);
	else if (root->type == OR)
		apply_or(exe_tool);
	else if (exe_tool->stop == TRUE)
		return ;
	else if (root->type == PIPE)
		open_pipe(exe_tool);
	else if (root->type == REDIRECT_APPEND)
		open_redirect_append(root, exe_tool);
	else if (root->type == REDIRECT_IN || root->type == HEREDOC)
		open_redirect_in(root, exe_tool);
	else if (root->type == REDIRECT_OUT)
		open_redirect_out(root, exe_tool);
	else if (root->type == BUILTIN)
		apply_built_in(root, exe_tool);
	else if (root->type == WORD)
		apply_command(root->command, exe_tool);
	check_exceptions(root, exe_tool);
	execute(root->right, exe_tool);
}
