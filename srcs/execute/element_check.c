/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:42:56 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/17 10:31:26 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_elements(t_tree_node *root, t_execute *exe_tool)
{
	if (root == NULL)
		return ;
	if (root->type == PIPE)
	{
		exe_tool->pipe_flag = EXIST;
		exe_tool->pipe_count++;
	}
	if (root->type == BUILTIN)
		exe_tool->built_in_flag = EXIST;
	check_elements(root->left, exe_tool);
	check_elements(root->right, exe_tool);
}