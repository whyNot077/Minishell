/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_key_to_value.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:47:12 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/28 14:21:45 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_the_key(char **value, size_t i)
{
	size_t	start;
	size_t	end;
	char	*key;

	if (!value || !*value)
		return (NULL);
	start = i + 1;
	end = start;
	while ((*value)[end] && !is_space((*value)[end]) && (*value)[end] != '$' \
		&& (*value)[end] != '\'' && (*value)[end] != '\"')
		end++;
	key = (char *)malloc(end - start + 1);
	if (!key)
		return (NULL);
	ft_memcpy(key, *value + start, end - start);
	key[end - start] = '\0';
	return (key);
}

static char	*get_key_value(char *key, char **env, size_t i)
{
	char	*env_value;
	size_t	key_length;

	key_length = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(key, env[i], key_length) == 0
			&& env[i][key_length] == '=')
		{
			env_value = env[i] + key_length + 1;
			return (ft_strdup(env_value));
		}
		(i)++;
	}
	return (ft_strdup(""));
}

void	replace_key_in_the_string(char **value, char *key, char *env_value, \
		size_t *i)
{
	char	*prefix;
	char	*suffix;
	char	*tmp;

	if (!value || !*value || !key || !env_value || !i)
		return ;
	prefix = ft_substr(*value, 0, *i);
	suffix = ft_substr(*value, *i + ft_strlen(key) + 1, \
		ft_strlen(*value) - (*i + ft_strlen(key) + 1));
	tmp = ft_strjoin(prefix, env_value);
	free(env_value);
	free(*value);
	*value = ft_strjoin(tmp, suffix);
	free(prefix);
	free(suffix);
	free(tmp);
}

void	replace_env_key_to_value(char **value, char **env)
{
	size_t	i;
	char	*key;
	char	*env_value;
	int		in_single_quote;
	int		in_double_quote;

	if (value == NULL || *value == NULL)
		return ;
	i = -1;
	in_single_quote = -1;
	in_double_quote = -1;
	while ((*value)[++i])
	{
		if ((*value)[i] == '\'' && in_double_quote == -1)
			in_single_quote *= -1;
		else if ((*value)[i] == '\"')
			in_double_quote *= -1;
		if ((*value)[i] == '$' && in_single_quote == -1)
		{
			key = get_the_key(value, i);
			env_value = get_key_value(key, env, 0);
			replace_key_in_the_string(value, key, env_value, &i);
			free(key);
		}
	}
}
