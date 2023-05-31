/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/31 19:08:29 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void free_everything(t_binarytree *tree, t_token *tokens, char *input)
{
	destroy_tree(&tree);
	free_tokens(&tokens);
	free(input);
	free(tokens);
}

static void	init_exe_tool(t_execute *exe_tool)
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
}

int	main(int argc, char *argv[], char *envp[])
{
	int				status;
	int				pid;
	char			*input;
	t_token			*tokens;
	t_binarytree	*tree;
	t_execute		*exe_tool;

	(void)envp;
	if (check_argc(argc, argv))
		return (0);
	exe_tool = envp_init(envp);
	while (1)    
	{
		exec_signal(READLINE_SIG);
		input = read_input(1);
		if (input)
		{
			tokens = create_tokens_by_lexical_analysis(input);
			tree = parse_tokens(tokens, exe_tool->env->data);
			if (tree && tree->root && tree->syntex_error == FALSE)
			{
				execute(tree->root, exe_tool);
				while (1)
				{
					pid = waitpid(-1, &status, 0);
					if (exe_tool->last_pid == pid)
						g_exit_code = WEXITSTATUS(status);
					else if (pid == -1)
						break ;
				}
				init_exe_tool(exe_tool);
			}
			free_everything(tree, tokens, input);
		}
	}
	free_envp(exe_tool);
	return (0);
}

