/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 19:32:28 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	leaks(void)
{
	system("leaks --list minishell > tmp.txt");
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
			tree = parse_tokens(tokens, envp);
			// execute(tree->root, exe_tool);
			display_tree(tree->root);
			destroy_tree(&tree);
			free_tokens(&tokens);
			free(input);
			free(tokens);
		}
	}
	free_envp(exe_tool);
	return (0);
}
