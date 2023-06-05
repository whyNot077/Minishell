/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:25:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/06/05 18:32:38 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	export(char **args, t_arraylist *envp, t_arraylist *export)
{
	g_exit_code = 0;
	if (args[1] == NULL)
	{
		print_export(export);
		return ;
	}
	get_args_to_envp(args, envp, export);
}
