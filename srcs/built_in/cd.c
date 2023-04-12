/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:05:25 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/12 11:01:25 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd(char **args)
{
	if (args[2] != NULL)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		g_exit_code = 1;
		return ;
	}
	else if (chdir(args[1]) != 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_code = 1;
		return ;
	}
	chdir(args[1]);
	g_exit_code = 0;
}
