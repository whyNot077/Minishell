/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg_validate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:51:35 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/23 16:04:23 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	validate_key_args(char **args, int args_idx)
{
	g_exit_code = 0;
	if (ft_isdigit(args[args_idx][0]) || !ft_isalpha(args[args_idx][0]))
	{
		if (args[args_idx][0] == '_')
			return (SUCCESS);
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(args[args_idx], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_exit_code = 1;
	}
	if (g_exit_code == 1)
		return (ERROR);
	return (SUCCESS);
}

int	check_same_key(char *str, t_arraylist *envp)
{
	int		envp_idx;
	int		str_idx;

	envp_idx = 0;
	while (envp->data[envp_idx])
	{
		str_idx = 0;
		while (str[str_idx] == envp->data[envp_idx][str_idx])
			str_idx++;
		if (envp->data[envp_idx][str_idx] == '=' && str[str_idx] == '\0')
			return (TRUE);
		envp_idx++;
	}
	return (FALSE);
}