/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:29:26 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/26 19:19:37 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	apply_envp(char **args, t_arraylist *envp, t_arraylist *export, \
						int idx)
{
	char	*export_str;
	char	*envp_str;
	
	if (ft_strchr(args[idx], '=') == NULL)
	{
		export_str = ft_strdup(args[idx]);
		al_add_rear(export, export_str);
	}
	else
	{
		export_str = ft_strdup(args[idx]);
		al_add_rear(export, export_str);
		envp_str = ft_strdup(args[idx]);
		al_add_rear(envp, envp_str);
	}
}

void	get_args_to_envp(char **args, t_arraylist *envp, t_arraylist *export)
{
	int		idx;

	idx = 1;
	while (args[++idx])
	{
		if (validate_key_args(args, idx) == ERROR)
			continue ;
		if (ft_strchr(args[idx], '=') == NULL && \
			check_same_key(args[idx], envp) == TRUE)
			continue ;
		apply_envp(args, envp, export, idx);
	}
}
