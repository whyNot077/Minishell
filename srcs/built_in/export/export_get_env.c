/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:29:26 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/30 15:35:45 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_has_same_key(char *str, t_arraylist *envp)
{
	int		envp_idx;
	int		str_idx;

	envp_idx = 0;
	while (envp->data[envp_idx])
	{
		str_idx = 0;
		while (str[str_idx] == envp->data[envp_idx][str_idx])
		{
			if (envp->data[envp_idx][str_idx] == '\0' && str[str_idx] == '\0')
				return (TRUE);
			str_idx++;
		}
		if (envp->data[envp_idx][str_idx] == '=' && str[str_idx] == '\0')
			return (TRUE);
		envp_idx++;
	}
	return (FALSE);
}

static void	apply_envp(char **args, t_arraylist *envp, t_arraylist *export, \
						int idx)
{
	char	*export_str;
	char	*envp_str;
	char	*key;

	key = get_key(args[idx]);
	if (ft_strchr(args[idx], '=') == NULL)
	{
		export_str = ft_strdup(args[idx]);
		al_add_rear(export, export_str);
	}
	else
	{
		apply_unset(key, envp, export);
		export_str = ft_strdup(args[idx]);
		al_add_rear(export, export_str);
		envp_str = ft_strdup(args[idx]);
		al_add_rear(envp, envp_str);
		free(key);
	}
}

void	get_args_to_envp(char **args, t_arraylist *envp, t_arraylist *export)
{
	int		idx;

	idx = 1;
	while (args[idx])
	{
		if (validate_key_args(args, idx) == ERROR)
		{
			idx++;
			continue ;
		}
		if (check_has_same_key(args[idx], export) == TRUE)
		{
			idx++;
			continue ;
		}
		apply_envp(args, envp, export, idx);
		idx++;
	}
}
