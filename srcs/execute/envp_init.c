/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:20:13 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/14 14:16:15 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_arraylist	*make_env_list(char **envp)
{
	t_arraylist	*env;
	int			i;

	i = 0;
	env = al_init();
	ft_printf("check2-1\n");
	while (envp[i])
	{
		al_add_rear(env, ft_strdup(envp[i]));
		i++;
	}
	ft_printf("check2-2\n");
	return (env);
}

void envp_init(t_execute *execute, char **envp)
{
	ft_printf("check1-1\n");
	execute->env = make_env_list(envp);
	ft_printf("check1-2\n");
	execute->export = make_env_list(envp);
}