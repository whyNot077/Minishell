/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 19:58:53 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/12 11:09:40 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_exit(char **args)
{
	if (args[1] == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		g_exit_code = 0;
		exit(0);
	}
	else if (ft_isdigit(args[1][0]) == 0) // 다 돌면서 확인
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exit_code = 2;
		exit(2);
	}
	else if (args[2] != NULL)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		g_exit_code = 127;
		//have to has error num 1
		return ;
	}
	else if (ft_atoi_extension(-9223372036854775807 > args[1] || \
										args[1] > 9223372036854775807) == 0)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exit_code = 2;
		exit(2);
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		g_exit_code = ft_atoi_extension(args[1]);
		exit(g_exit_code);
	}
}
