/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:41:08 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/07 17:28:30 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_argc(int argc, char *argv[])
{
	(void)argv;
	if (argc != 1)
	{
		printf("Do not input any arguments");
		return (ERROR);
	}
	return (0);
}
