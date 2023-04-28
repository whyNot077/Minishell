/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:07:17 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/23 13:48:00 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	sort_env(t_arraylist *envp)
{
	int		idx;
	int		idx2;
	char	*tmp;

	idx = 0;
	while (envp->data[idx])
	{
		idx2 = idx + 1;
		while (envp->data[idx2])
		{
			if (ft_strcmp(envp->data[idx], envp->data[idx2]) > 0)
			{
				tmp = envp->data[idx];
				envp->data[idx] = envp->data[idx2];
				envp->data[idx2] = tmp;
			}
			idx2++;
		}
		idx++;
	}
}

static void print_value(t_arraylist *envp, int outfile_fd, \
						int *envp_idx, int *str_idx)
{
	ft_putchar_fd('=', outfile_fd);
	ft_putchar_fd('"', outfile_fd);
	while (envp->data[*envp_idx][++(*str_idx)])
		ft_putchar_fd(envp->data[*envp_idx][*str_idx], outfile_fd);
	ft_putchar_fd('"', outfile_fd);
	ft_putchar_fd('\n', outfile_fd);
}

void	print_export(t_arraylist *envp, int outfile_fd)
{
	int		envp_idx;
	int		str_idx;

	sort_env(envp);
	envp_idx = 0;
	while (envp->data[envp_idx])
	{
		ft_putstr_fd("declare -x ", outfile_fd);
		str_idx = -1;
		while (envp->data[envp_idx][++str_idx])
		{
			if (envp->data[envp_idx][str_idx] == '=')
				break ;
			ft_putchar_fd(envp->data[envp_idx][str_idx], outfile_fd);
		}
		if (envp->data[envp_idx][str_idx] != '=')
		{
			ft_putchar_fd('\n', outfile_fd);
			envp_idx++;
			continue;
		}
		print_value(envp, outfile_fd, &envp_idx, &str_idx);
		envp_idx++;
	}
}
