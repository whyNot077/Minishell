/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:22:43 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/25 13:39:26 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


static int get_target_index(char *str, t_arraylist *envp)
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
			return (envp_idx);
		envp_idx++;
	}
	return (ERROR);
}

static void	unset_str_in_array(char *str, t_arraylist *env)
{
	int		target_idx;

	target_idx = get_target_index(str, env);
	if (target_idx == ERROR)
		return ;
	al_remove(env, target_idx);
}

void apply_unset(char *str, t_arraylist *env, t_arraylist *export)
{
	unset_str_in_array(str, env);
	unset_str_in_array(str, export);
}
