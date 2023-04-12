/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:25:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/10 21:23:44 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	validate_key_args(char **args)
{
	int		args_idx;
	int		str_idx;
	
	args_idx = 1;
	while (args[args_idx])
	{
		while (args[args_idx][str_idx])
		{
			if (ft_isdigit(args[1][str_idx]) || !ft_isalpha(args[1][str_idx]))
			{
				if (args[1][str_idx] == '_')
				{
					str_idx++;
					continue ;
				}
				ft_putstr_fd("bash: export: `", 2);
				ft_putchar_fd(args[1][str_idx], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				g_exit_code = 1;
			}
			str_idx++;
		}
		args_idx++;
	}
	if (g_exit_code == 1)
		return (ERROR);
	return (SUCCESS);
}

static void	print_env(char **envp, int outfile_fd)
{
	char	**sorted_envp;
	
	sorted_envp = sort_envp(envp);
	while (*sorted_envp)
	{
		ft_putstr_fd("declare -x ", outfile_fd);
		ft_putstr_fd(*sorted_envp, outfile_fd);
		ft_putchar_fd('\n', outfile_fd);
		sorted_envp++;
	}
	free(sorted_envp);
}

static void	get_args_to_envp(char **args, char **envp, char **export)
{
	// 1. check if there is only key in args
	// 1-1 if there is only key, check if there is key in args
	if (ft_strchr(args[1], '=') == NULL)
	{
		
	}
	// 2. check if there is key and value in args
	
}

void	export(char **args, char **envp, char **export, int outfile_fd)
{
	// 1. check if there is wrong key
	if (validate_key_args(args) == ERROR)
		return ;
	// 2. write envp to outfile_fd
	if (args[1] == NULL)
	{
		print_env(envp, outfile_fd);
		return ;
	}
	// 3. input key and value to envp
	get_args_to_envp(args, envp, export);
}
