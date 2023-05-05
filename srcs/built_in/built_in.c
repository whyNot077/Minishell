/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:06 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/05 18:24:13 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in(char **args, t_execute *execute)
{
	if (ft_strcmp(args[0], "echo") == 0)
		echo(args, execute);
	else if (ft_strcmp(args[0], "cd") == 0)
		cd(args, execute);
	else if (ft_strcmp(args[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		export(args, execute->env, execute->export, execute->outfile_fd);
	else if (ft_strcmp(args[0], "unset") == 0)
		unset(args, execute->env, execute->export);
	else if (ft_strcmp(args[0], "env") == 0)
		env(execute->env);
	else if (ft_strcmp(args[0], "exit") == 0)
		command_exit(args);
	if (execute->outfile_fd > 0)
	{
		dup2(execute->dup_tmp, STDOUT_FILENO);
		close(execute->outfile_fd);
	}
}
