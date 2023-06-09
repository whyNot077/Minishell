/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/09 14:37:46 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_and_execute(char *input, t_execute *exe_tool)
{
	t_token			*tokens;
	t_binarytree	*tree;

	tokens = create_tokens_by_lexical_analysis(input);
	tree = parse_tokens(&tokens, exe_tool->env->data);
	if (tree && tree->root && tree->syntex_error == FALSE)
	{
		execute(tree->root, exe_tool);
		get_pid_and_signal(exe_tool);
		init_exe_tool(exe_tool);
	}
	free_everything(tree, tokens, input);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	t_execute	*exe_tool;

	if (check_argc(argc, argv))
		return (0);
	exe_tool = envp_init(envp);
	while (1)
	{
		exec_signal(READLINE_SIG);
		input = read_input(1);
		if (input)
		{
			parse_and_execute(input, exe_tool);
		}
	}
	free_envp(exe_tool);
	return (0);
}
