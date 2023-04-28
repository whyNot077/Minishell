/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:25:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/26 19:15:30 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	export(char **args, t_arraylist *envp, t_arraylist *export,\
				 int outfile_fd)
{
	(void)envp;
	// 2. write envp to outfile_fd
	if (args[2] == NULL)
	{
		print_export(export, outfile_fd);
		return ;
	}
	// 3. input key and value to envp
	get_args_to_envp(args, envp, export);
}
