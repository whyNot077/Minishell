/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/29 14:00:45 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(t_binarytree *tree, t_execute *exe_tool)
{
	// no pipe, built_in exist
	if (tree->root->type == BUILTIN)
		built_in(tree->root->command, exe_tool);
}
