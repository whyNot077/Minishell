/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:42:56 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/14 19:19:03 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_elements(t_tree_node *root, t_execute *exe_tool)
{
	while (root->left)
	{
		if (root->type == PIPE)
		{
			exe_tool->pipe_flag = EXIST;
			exe_tool->pipe_count++;
		}
		root = root->left;
	}
}