/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nomal_change_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:42:38 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/08 21:27:31 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	apply_normal_cd(t_execute *execute)
{
	char	*home_value;
	char	*pwd_value;

	home_value = get_target_value("HOME", execute->env);
	pwd_value = getcwd(NULL, 0);
	if (pwd_value == NULL)
	{
		g_exit_code = 1;
		ft_putstr_fd("bash: cd: No such file or directory\n", 2);
	}
	chdir(home_value);
	apply_cd(execute, pwd_value);
}
