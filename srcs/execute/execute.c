/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/20 19:54:32 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	reset_exe_tool(t_execute *exe_tool)
// {
// 	exe_tool->pipe_flag = NOT_EXIST;
// 	exe_tool->built_in_flag = NOT_EXIST;
// 	exe_tool->pipe_count = 0;
// }

// void	execute(t_tree_node *root, t_execute *exe_tool)
// {
// 	// check pipe, built_in
// 	reset_exe_tool(exe_tool);
// 	check_elements(root, exe_tool);
// 	// no pipe, built_in exist
// 	if (exe_tool->built_in_flag == EXIST && exe_tool->pipe_flag == NOT_EXIST)
// 	built_in(exe_tool);
// 	// pipe exist
// 	else if (exe_tool->pipe_flag == EXIST)
// 		pipe_execute(root, exe_tool);
// }
