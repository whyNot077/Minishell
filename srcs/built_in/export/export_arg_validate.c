/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg_validate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:51:35 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/05 17:25:12 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	validate_key_args(char **args, int args_idx)
{
	if (ft_isdigit(args[args_idx][0]) || !ft_isalpha(args[args_idx][0]))
	{
		if (args[args_idx][0] == '_')
			return (SUCCESS);
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(args[args_idx], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_exit_code = 1;
		return (ERROR);
	}
	return (SUCCESS);
}

int	check_has_same_str(char *str, t_arraylist *envp)
{
	int		envp_idx;

	envp_idx = 0;
	while (envp->data[envp_idx])
	{
		if (ft_strcmp(str, envp->data[envp_idx]) == 0)
			return (TRUE);
		envp_idx++;
	}
	return (FALSE);
}

char	*get_key(char *str)
{
	int		idx;
	char	*key;

	if (ft_strchr(str, '=') == NULL)
		return (str);
	idx = 0;
	while (str[idx] != '=')
		idx++;
	key = ft_substr(str, 0, idx);
	return (key);
}
