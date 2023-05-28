/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choihyojong <choihyojong@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 19:58:53 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/28 02:08:06 by choihyojong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	validate_arg_is_num(char **args)
{
	int	str_idx;

	str_idx = 0;
	while (args[1][str_idx])
	{
		if (ft_isdigit(args[1][str_idx]) == FALSE)
		{
			if (args[1][0] == '-')
			{
				str_idx++;
				continue ;
			}
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_exit_code = 2;
			exit(2);
		}
		str_idx++;
	}
}

static int	validate_arg_count(char **args)
{
	int	arg_idx;

	arg_idx = 0;
	while (args[arg_idx])
		arg_idx++;
	if (arg_idx >= 2)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

static	void	validate_arg_range(char **args)
{
	long long int	num;
	char			*res;

	num = ft_atoi_extension(args[1]);
	res = ft_itoa_extension(num);
	if (ft_strlen(res) != ft_strlen(args[1]) && \
		ft_strcmp(res, args[1]) != 0)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exit_code = 2;
		exit(2);
	}
}

static void	numbering_exit(char **args)
{
	long long int	num;
	long long int	key;

	num = ft_atoi_extension(args[1]);
	ft_putstr_fd("exit\n", 1);
	key = num;
	while (key < 0)
		key += 256;
	g_exit_code = (key % 256);
	exit(g_exit_code);
}

void	command_exit(char **args, t_execute *exe_tool)
{	
	if ((args[1] == NULL && exe_tool->pipe_flag == TRUE) || \
		(args[1] == NULL && exe_tool->exit_flag == TRUE))
	{
		g_exit_code = 0;
		exit(0);
	}
	if (args[1] == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		g_exit_code = 0;
		exit(0);
	}
	validate_arg_is_num(args);
	if (validate_arg_count(args) == FALSE)
	{
		g_exit_code = 1;
		return ;
	}
	validate_arg_range(args);
	numbering_exit(args);
}
