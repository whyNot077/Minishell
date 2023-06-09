/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_open.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:17:29 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/09 11:06:18 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	open_output_file(char *arg, t_execute *exe_tool)
{
	int	fd;

	fd = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ERROR);
	exe_tool->outfile_fd = fd;
	return (SUCCESS);
}

static int	open_input_file(char *arg, t_execute *exe_tool)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		return (ERROR);
	}
	exe_tool->infile_fd = fd;
	return (SUCCESS);
}

void	open_redirect_out(t_tree_node *root, t_execute *exe_tool)
{
	if (exe_tool->open_error == TRUE)
		return ;
	if (open_output_file(root->filename, exe_tool) == ERROR)
	{
		ft_putstr_fd("minishell: ", STDOUT_FILENO);
		ft_putstr_fd(root->filename, STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
		g_exit_code = 1;
	}
}

void	open_redirect_in(t_tree_node *root, t_execute *exe_tool)
{
	if (exe_tool->open_error == TRUE)
		return ;
	if (open_input_file(root->filename, exe_tool) == ERROR)
	{
		ft_putstr_fd("minishell: ", STDOUT_FILENO);
		ft_putstr_fd(root->filename, STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
		g_exit_code = 1;
		exe_tool->open_error = TRUE;
		exe_tool->open_error_for_and_or = TRUE;
	}
}
