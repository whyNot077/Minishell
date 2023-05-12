/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:06 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/11 19:36:34 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in(char **args, t_execute *exe_tool)
{
	printf("built_in\n");
	// apply_redirect_out(exe_tool);
	if (ft_strcmp(args[0], "echo") == 0)
		echo(args, exe_tool);
	else if (ft_strcmp(args[0], "cd") == 0)
		cd(args, exe_tool);
	else if (ft_strcmp(args[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		export(args, exe_tool->env, exe_tool->export, exe_tool->outfile_fd);
	else if (ft_strcmp(args[0], "unset") == 0)
		unset(args, exe_tool->env, exe_tool->export);
	else if (ft_strcmp(args[0], "env") == 0)
		env(exe_tool->env);
	else if (ft_strcmp(args[0], "exit") == 0)
		command_exit(args);
	// restore_redirect_out(exe_tool);
}
