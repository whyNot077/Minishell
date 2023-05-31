/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:56:03 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/31 19:20:10 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_output_file(char *filename, t_execute *exe_tool)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == ERROR)
		return (ERROR);
	exe_tool->outfile_fd = fd;
	return (SUCCESS);
}

void	open_redirect_append(t_tree_node *root, t_execute *exe_tool)
{
	if (open_output_file(root->filename, exe_tool) == ERROR)
	{
		ft_putstr_fd("minishell: ", STDOUT_FILENO);
		ft_putstr_fd(root->filename, STDOUT_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
	}
}
