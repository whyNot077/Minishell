/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:29:26 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/14 19:46:07 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	get_args_to_envp(char **args, char **envp, char **export)
{
	// 1. check if there is only key in args
	// 1-1 if there is only key, check if there is key in args
	if (ft_strchr(args[1], '=') == NULL)
		al_add_rear(export, args[1]);
	// 2. check if there is key and value in args
	else
	{
		al_add_rear(export, args[1]);
		al_add_rear(envp, args[1]);
	}
}