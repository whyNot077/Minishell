/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:05:31 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/07 14:06:38 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_input(void)
{
	char	*input;

	printf("%sMinishell >%s", BLUE, DEFAULT);
	input = readline(" ");
	if (input && *input)
		add_history(input);
	return (input);
}
