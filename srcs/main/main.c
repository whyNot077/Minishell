/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/11 13:57:17 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void leaks(void)
{
	system("leaks --list minishell > tmp.txt");
}


int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_token	*tokens;

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
		free(input);
		free_tokens(&tokens);
	}
	return (0);
}
