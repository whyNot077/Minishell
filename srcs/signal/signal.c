/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:33:16 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/30 15:41:16 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_signal(int flag)
{
	struct sigaction sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (flag == PARENT)
	{
		exec_parent_signal(sa);
	}
	else if (flag == CHILD)
	{
		exec_child_signal(sa);
	}
	else if (flag == HEREDOC)
	{
		exec_heredoc_signal(sa);
	}
	else
	{
		exec_readline_signal(sa);
	}
}
