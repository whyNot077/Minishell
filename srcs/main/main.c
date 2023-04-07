/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/07 12:59:17 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *read_input(void)
{
    char	*input;

	input = readline(" ");
    if (input && *input)
        add_history(input);
    return (input);
}

int	main()
{
    char	*input;

    while (1)
	{
		printf("%sminishell >%s", BLUE, DEFAULT);
        input = read_input();
		if (input == NULL)
			break ;
    }

    return 0;
}
