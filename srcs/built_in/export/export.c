/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:25:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/14 16:37:49 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	export(char **args, t_arraylist *envp, t_arraylist *export)
{
	if (args[1] == NULL)
	{
		print_export(export);
		return ;
	}
	get_args_to_envp(args, envp, export);
}
