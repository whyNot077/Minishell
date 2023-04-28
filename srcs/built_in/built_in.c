/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:06 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/24 14:48:39 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in(char **args, t_execute *execute)
{
	if (ft_strcmp(args[1], "echo") == 0)
		echo(args, execute);
	else if (ft_strcmp(args[1], "cd") == 0)
		cd(args, execute);
	else if (ft_strcmp(args[1], "pwd") == 0)
		pwd();
	else if (ft_strcmp(args[1], "export") == 0)
		export(args, execute->env, execute->export, execute->outfile_fd);
	else if (ft_strcmp(args[1], "unset") == 0)
		unset(args, execute->env, execute->export);
	else if (ft_strcmp(args[1], "env") == 0)
		env(execute->env, execute->outfile_fd);
	else if (ft_strcmp(args[1], "exit") == 0)
		command_exit(args);
}
