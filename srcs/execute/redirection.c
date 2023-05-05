/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:17:29 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/05 18:57:34 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int open_output_file(char *arg, t_execute *exe_tool)
{
	int fd;

	fd = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ERROR);
	exe_tool->outfile_fd = fd;
	exe_tool->dup_tmp = dup(STDOUT_FILENO);
	dup2(exe_tool->outfile_fd, STDOUT_FILENO);
	return (SUCCESS);
}

static int open_input_file(char *arg, t_execute *exe_tool)
{
	int fd;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	exe_tool->infile_fd = fd;
	exe_tool->dup_tmp = dup(STDIN_FILENO);
	dup2(exe_tool->infile_fd, STDIN_FILENO);
	return (SUCCESS);
}

void	apply_redirect_out(t_tree_node *root, t_execute *exe_tool)
{
	if (open_output_file(root->filename, exe_tool) == ERROR)
	{
		ft_putstr_fd("minishell: ", STDOUT_FILENO);
		ft_putstr_fd(root->filename, STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
	}
}

void	apply_redirect_in(t_tree_node *root, t_execute *exe_tool)
{
	if (open_input_file(root->filename, exe_tool) == ERROR)
	{
		ft_putstr_fd("minishell: ", STDOUT_FILENO);
		ft_putstr_fd(root->filename, STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
	}
}
