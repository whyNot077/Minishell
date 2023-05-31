/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:05:31 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/31 18:32:24 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_input(int display_prompt)
{
	char	*input;
	char	*prompt;

	if (display_prompt)
	{
		prompt = "Minishell$ ";
		input = readline(prompt);
	}
	else
	{
		input = readline(NULL);
	}
	if (input == NULL)
	{
		exit(0);
	}
	if (input && *input)
	{
		add_history(input);
	}
	return (input);
}

static void	readline_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 130;
	}
}

void	exec_readline_signal(struct sigaction sa)
{
	sa.sa_handler = readline_signal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}
