/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 19:58:53 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/23 20:29:30 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	validate_arg_is_num(char **args)
{
	int str_idx;

	str_idx = 0;
	while (args[2][str_idx])
	{
		if (ft_isdigit(args[2][str_idx]) == FALSE)
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(args[2], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_exit_code = 2;
			exit(2);
		}
		str_idx++;
	}
}

static void	validate_arg_count(char **args)
{
	int arg_idx;

	arg_idx = 0;
	while (args[arg_idx])
		arg_idx++;
	if (arg_idx > 3)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		g_exit_code = 1;
		ft_printf("g_exit_code : %d\n", g_exit_code);
		exit(1);
	}
}

static void validate_arg_range(char **args)
{
	if (-9223372036854775807 > ft_atoi_extension(args[2]) || \
			ft_atoi_extension(args[2]) > 9223372036854775807)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(args[2], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exit_code = 2;
		ft_printf("g_exit_code(range) : %d\n", g_exit_code);
		exit(2);
	}
}

static void numbering_exit(char **args)
{
	ft_putstr_fd("exit\n", 1);
	g_exit_code = (ft_atoi_extension(args[2]) % 256);
	ft_printf("g_exit_code(numbering) : %d\n", g_exit_code);
	exit(g_exit_code);
}

void	command_exit(char **args)
{
	if (args[2] == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		g_exit_code = 0;
		ft_printf("g_exit_code : %d\n", g_exit_code);
		exit(0);
	}
	validate_arg_is_num(args);
	validate_arg_count(args);
	validate_arg_range(args);
	numbering_exit(args);
}
