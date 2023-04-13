/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 14:36:40 by minkim3          ###   ########.fr       */
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
	binarytree	*tree;

	(void)envp;
	atexit(leaks);
	if (check_argc(argc, argv))
		return (0);
	signal_handler();
	while (1)
	{
		display_prompt();
		input = read_input();
		tokens = create_tokens_by_lexical_analysis(input);
		tree = parse_tokens(tokens);
		display_tree(tree);
		destroy_tree(&tree);
		free(input);
		free(tokens);
	}
	return (0);
}
