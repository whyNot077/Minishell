/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 14:32:33 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void leaks(void)
{
	system("leaks --list minishell > tmp.txt");
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*input;
	t_token		*tokens;
	t_binarytree	*tree;
	t_execute	*execute;

	(void)envp;
	atexit(leaks);
	if (check_argc(argc, argv))
		return (0);
	signal_handler();
	execute = envp_init(envp);
	while (1)
	{
		display_prompt();
		input = read_input();
		tokens = create_tokens_by_lexical_analysis(input);
		tree = parse_tokens(tokens);
		display_tree(tree->root);
		destroy_tree(&tree);
		free_tokens(&tokens);
		free(input);
		free(tokens);
	}
	free_envp(execute);
	return (0);
}
