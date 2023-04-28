/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:25:37 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/26 16:00:05 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int validate_chdir(char **args, char *pwd_value)
{
	if (chdir(args[2]) != 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(pwd_value);
		g_exit_code = 1;
		return (ERROR);
	}
	return (SUCCESS);
}