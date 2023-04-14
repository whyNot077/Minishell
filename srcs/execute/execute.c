/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/14 16:02:57 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_elements()
{
	// check built_in

	// check pipe
	
}

void	execute(t_tree_node *root, t_execute *exe_tool)
{
	(void)root;
	(void)exe_tool;
	// check_elements();
	// // no pipe, built_in exist
	// if (exe_tool->built_in_flag == EXIST && exe_tool->pipe_flag == NOT_EXIST)
	// 	built_in();
}
