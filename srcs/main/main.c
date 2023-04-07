/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/07 17:41:30 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_token	*tokens;
	int		i;

	(void)envp;
	if (check_argc(argc, argv))
		return (0);
	while (1)
	{
		printf("%sMinishell >%s", BLUE, DEFAULT);
		input = read_input();
		if (input == NULL)
			break ;
		tokens = create_tokens_by_lexical_analysis(input);
		if (tokens == NULL)
			break ;
		for (i = 0; tokens[i].value != NULL; i++)
			printf("type: %d, value: %s\n", tokens[i].type, tokens[i].value);
		free(input);
		free_tokens(tokens);
	}
	return (0);
}
