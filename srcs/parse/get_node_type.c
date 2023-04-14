/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:18:59 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 21:13:59 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	replace_env_to_the_word(char **value, char **env)
{
	char	*env_key;
	char	*env_value;
	size_t	key_length;
	int		i;

	if (!value || !*value || !env)
		return ;
	if ((*value)[0] == '$')
	{
		env_key = *value + 1;
		key_length = ft_strlen(env_key);
		i = 0;
		while (env[i])
		{
			if (ft_strncmp(env_key, env[i], key_length) == 0 \
				&& env[i][key_length] == '=')
			{
				env_value = env[i] + key_length + 1;
				free(*value);
				*value = ft_strdup(env_value);
				return ;
			}
			i++;
		}
		free(*value);
		*value = strdup("");
	}
}

int get_node_type(char **value, char **env)
{
    if (value == NULL || *value == NULL)
        return (ERROR);
    if ((*value)[0] == '$')
    {
        replace_env_to_the_word(value, env);
        return (WORD);
    }
    else if ((*value)[0] == '-')
        return (OPTION);
    else
    {
        if (is_builtin(*value))
            return (BUILTIN);
        else
        {
            // replace_the_env_in_string(value, env);
            return (WORD);
        }
    }
}
