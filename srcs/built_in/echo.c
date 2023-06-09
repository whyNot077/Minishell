/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:17:23 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/09 20:56:13 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	validate_n_option(char **args, int *args_idx, int *n_option_flag, \
								int *current_n_flag)
{
	int		string_idx;

	string_idx = 1;
	if (args[1][1] == 'n' && args[1][2] != '\0')
	{
		*current_n_flag = 1;
		string_idx = 3;
		return ;
	}
	while (args[*args_idx][string_idx])
	{
		*n_option_flag = 1;
		if (args[*args_idx][string_idx] != 'n')
		{
			*current_n_flag = 1;
			break ;
		}
		string_idx++;
	}
}

static void	find_print_idx(char **args, int *args_idx, int *n_option_flag)
{
	int		current_n_flag;

	current_n_flag = 0;
	while (args[*args_idx])
	{
		if (args[*args_idx][0] == '-')
		{
			validate_n_option(args, args_idx, n_option_flag, &current_n_flag);
		}
		else
			break ;
		if (current_n_flag == 1)
			break ;
		(*args_idx)++;
	}
}

void	echo(char **args, t_execute *execute)
{
	int		args_idx;
	int		n_option_flag;

	(void)execute;
	args_idx = 1;
	n_option_flag = 0;
	g_exit_code = 0;
	find_print_idx(args, &args_idx, &n_option_flag);
	while (args[args_idx])
	{
		ft_putstr_fd(args[args_idx], STDOUT_FILENO);
		if (args[args_idx + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		args_idx++;
	}
	if (n_option_flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
