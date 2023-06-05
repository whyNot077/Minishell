/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:40:08 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/05 18:17:41 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(void)
{
	char	*pwd;

	g_exit_code = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("bash: pwd: No such file or directory\n", 2);
		g_exit_code = 1;
		return ;
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(pwd);
}
