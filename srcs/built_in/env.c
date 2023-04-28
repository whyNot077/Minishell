/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:59:09 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/23 18:32:23 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_arraylist *envp, int outfile_fd)
{
	int	idx;

	idx = 0;
	while (envp->data[idx])
	{
		ft_putstr_fd(envp->data[idx], outfile_fd);
		ft_putstr_fd("\n", outfile_fd);
		idx++;
	}
}