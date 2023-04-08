/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:17:23 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/07 22:05:20 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char **args)
{
	int		args_idx;
	int		string_idx;
	int		n_option_flag;

	args_idx = 1;
	n_option_flag = 0;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		n_option_flag = 1;
		args_idx++;
	}
	while (args[args_idx])
	{
		ft_putstr_fd(args[args_idx], 1);
		if (args[args_idx + 1])
			ft_putchar_fd(' ', 1);
		args_idx++;
	}
	if (n_option_flag == 0)
		ft_putchar_fd('\n', 1);
}
