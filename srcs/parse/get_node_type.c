/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:18:59 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 20:19:03 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	change_env_to_word(char **value, char **env)
// {
// 	// Your implementation for changing the environment variable to a word
// }

static int	is_builtin(char *value)
{
	if (ft_strcmp(value, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "export") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(value, "exit") == 0)
		return (TRUE);
	else
		return (FALSE);
}

int	get_node_type(char *value, char **env)
{
	(void)env;
	if (value == NULL)
		return (ERROR);
	if (value[0] == '$')
	{
		// change_env_to_word(&value, env);
		return (WORD);
	}
	else if (value[0] == '-')
		return (OPTION);
	else
	{
		if (is_builtin(value))
			return (BUILTIN);
		else
		{
			// replace_env_to_word(&value, env);
			return (WORD);
		}
	}
}