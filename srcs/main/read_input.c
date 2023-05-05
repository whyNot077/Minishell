/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:05:31 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/05 19:26:26 by hyojocho         ###   ########.fr       */
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
		error_exit("exit");
	}
	if (input && *input)
	{
		add_history(input);
	}
	return (input);
}

void	handle_readline(char *input)
{
	rl_clear_history();
	rl_on_new_line();
	rl_replace_line(input, 0);
}
