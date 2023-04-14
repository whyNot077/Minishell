/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:20:13 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/14 20:52:07 by minkim3          ###   ########.fr       */
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

static void	al_destroy(t_arraylist *list)
{
	if (list)
	{
		if (list->data)
		{
			free(list->data);
			list->data = NULL;
		}
		free(list);
	}
}

void	free_envp(t_execute *execute)
{
	int	i;

	if (execute->env)
	{
		i = 0;
		while (execute->env->data[i])
		{
			free(execute->env->data[i]);
			i++;
		}
		al_destroy(execute->env);
	}
	if (execute->export)
	{
		i = 0;
		while (execute->export->data[i])
		{
			free(execute->export->data[i]);
			i++;
		}
		al_destroy(execute->export);
	}
}

t_execute	*envp_init(char **envp)
{
	t_execute	*execute;

	execute = ft_calloc(1, sizeof(t_execute));
	execute->env = make_env_list(envp);
	execute->export = make_env_list(envp);
	return (execute);
}
