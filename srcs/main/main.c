/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/15 20:49:03 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	leaks(void)
// {
// 	system("leaks --list minishell > tmp.txt");
// }

static void free_everything(t_binarytree *tree, t_token *tokens, char *input)
{
	destroy_tree(&tree);
	free_tokens(&tokens);
	free(input);
	free(tokens);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*input;
	t_token			*tokens;
	t_binarytree	*tree;
	t_execute		*exe_tool;

	(void)envp;
	// atexit(leaks);
	if (check_argc(argc, argv))
		return (0);
	signal_handler();
	exe_tool = envp_init(envp);
	while (1)
	{
		input = read_input(1);
		if (input)
		{
			tokens = create_tokens_by_lexical_analysis(input);
			tree = parse_tokens(tokens, exe_tool->env->data);
			if (tree && tree->root && tree->syntex_error == FALSE)
			{
				execute(tree->root, exe_tool);
				while (waitpid(-1, NULL, 0) != -1)
					;
				memset(exe_tool->pipe_fd, 0, sizeof(int) * 2);
				exe_tool->prev_fd = 0;
			}
			free_everything(tree, tokens, input);
		}
	}
	free_envp(exe_tool);
	return (0);
}
