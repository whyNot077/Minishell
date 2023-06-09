/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:06 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/09 11:03:39 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in(char **args, t_execute *exe_tool)
{
	apply_redirect_out(exe_tool);
	if (ft_strcmp(args[0], "echo") == 0)
		echo(args, exe_tool);
	else if (ft_strcmp(args[0], "cd") == 0)
		cd(args, exe_tool);
	else if (ft_strcmp(args[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		export(args, exe_tool->env, exe_tool->export);
	else if (ft_strcmp(args[0], "unset") == 0)
		unset(args, exe_tool->env, exe_tool->export);
	else if (ft_strcmp(args[0], "env") == 0)
		env(exe_tool->env);
	else if (ft_strcmp(args[0], "exit") == 0)
		command_exit(args, exe_tool);
	restore_redirect_out(exe_tool);
}
