/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:02:40 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/26 14:49:42 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	validate_unset_element(char *str)
{
	if (ft_strchr(str, '=') == FALSE)
		return (SUCCESS);
	return (ERROR);
}

void	unset(char **args, t_arraylist *envp, t_arraylist *export)
{
	int	args_idx;

	args_idx = 1;
	while (args[args_idx])
	{
		if (validate_unset_element(args[args_idx]) == ERROR)
		{
			args_idx++;
			continue ;
		}
		apply_unset(args[args_idx], envp, export);
		args_idx++;
	}
}
