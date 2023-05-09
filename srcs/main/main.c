/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/09 16:11:05 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	leaks(void)
{
	system("leaks --list minishell > tmp.txt");
}

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
	atexit(leaks);
	if (check_argc(argc, argv))
		return (0);
	signal_handler();
	exe_tool = envp_init(envp);
	while (1)
	{
		input = read_input(1);
		if (input)
		{
			handle_readline(input);
			tokens = create_tokens_by_lexical_analysis(input);
			tree = parse_tokens(tokens, exe_tool->env->data);
			if (tree && tree->root && tree->syntex_error == FALSE)
				execute(tree->root, exe_tool);
			// if (tree->syntex_error == FALSE)
			// 	display_tree(tree->root, exe_tool->env->data, exe_tool);
			free_everything(tree, tokens, input);
		}
	}
	free_envp(exe_tool);
	return (0);
}
