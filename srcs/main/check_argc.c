/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:41:08 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/06 17:57:46 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_argc(int argc, char *argv[])
{
	(void)argv;
	if (argc != 1)
	{
		printf("Do not input any arguments");
		return (ERROR);
	}
	return (0);
}

void	free_everything(t_binarytree *tree, t_token *tokens, char *input)
{
	destroy_tree(&tree);
	free_tokens(&tokens);
	free(input);
	free(tokens);
}

void	init_exe_tool(t_execute *exe_tool)
{
	exe_tool->pipe_flag = FALSE;
	exe_tool->curr_pipe_flag = FALSE;
	exe_tool->exit_flag = FALSE;
	exe_tool->built_in_flag = FALSE;
	exe_tool->pipe_fd[0] = 0;
	exe_tool->pipe_fd[1] = 0;
	exe_tool->prev_fd = 0;
	exe_tool->infile_fd = 0;
	exe_tool->outfile_fd = 0;
	exe_tool->dup_tmp = 0;
	exe_tool->error = 0;
}
