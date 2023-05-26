/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:46:00 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/26 14:49:00 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_target_value(char *str, t_arraylist *envp)
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
			return (*(envp->data + envp_idx) + str_idx + 1);
		envp_idx++;
	}
	return (NULL);
}

int	get_env_value(char *str, t_arraylist *envp)
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
			return (SUCCESS);
		envp_idx++;
	}
	return (ERROR);
}
