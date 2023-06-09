/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/09 12:16:15 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	apply_built_in(t_tree_node *root, t_execute *exe_tool)
{
	if ((root->type == BUILTIN && exe_tool->pipe_flag == FALSE \
			&& exe_tool->open_error == FALSE) || \
		(root->type == BUILTIN && exe_tool->pipe_flag == FALSE \
				&& exe_tool->and_or_flag == TRUE))
	{
		exe_tool->execute_error = FALSE;
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
		exe_tool->execute_error = FALSE;
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

static void	apply_and(t_execute *exe_tool)
{
	int	pid;
	int	status;


	while (exe_tool->num_of_executed_commands)
	{
		pid = waitpid(-1, &status, 0);
		if (exe_tool->last_pid == pid)
		{
			g_exit_code = WEXITSTATUS(status);
			break ;
		}
		exe_tool->num_of_executed_commands--;
	}
	if ((exe_tool->open_error == FALSE) && g_exit_code == 0)
	{
		init_exe_tool(exe_tool);
	}
	else
		exe_tool->stop = TRUE;
}

static void	apply_or(t_execute *exe_tool)
{
	int	pid;
	int	status;
	int	num_commands;


	num_commands = exe_tool->num_of_executed_commands;
	while (exe_tool->num_of_executed_commands)
	{
		pid = waitpid(-1, &status, 0);
		if (exe_tool->last_pid == pid)
		{
			g_exit_code = WEXITSTATUS(status);
			break ;
		}
		exe_tool->num_of_executed_commands--;
	}
	if ((exe_tool->open_error_for_and_or == FALSE && num_commands == 0) || g_exit_code == 0)
	{
		exe_tool->stop = TRUE;
	}
	else
	{
		init_exe_tool(exe_tool);
	}
}

void	execute(t_tree_node *root, t_execute *exe_tool)
{
	if (root == NULL)
		return ;
	execute(root->left, exe_tool);
	// printf("value: %s\n", root->value);
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
