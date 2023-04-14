/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:20:13 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/14 14:50:58 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_arraylist	*make_env_list(char **envp)
{
	t_arraylist	*env;
	int			i;

	i = 0;
	env = al_init();
	while (envp[i])
	{
		al_add_rear(env, ft_strdup(envp[i]));
		i++;
	}
	return (env);
}

void	free_envp(t_execute	*execute)
{
	int	i;

	i = 0;
	while (&(execute->env[i]))
	{
		free(&(execute->env[i]));
		i++;
	}
	free(execute->env);
	i = 0;
	while (&(execute->export[i]))
	{
		free(&(execute->export[i]));
		i++;
	}
	free(execute->export);
}

t_execute	*envp_init(char **envp)
{
	t_execute *execute;

	execute = ft_calloc(1, sizeof(t_execute));
	execute->env = make_env_list(envp);
	execute->export = make_env_list(envp);
	return (execute);
}
