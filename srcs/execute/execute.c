/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/05/04 15:36:59 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(t_tree_node *root, t_execute *exe_tool)
{
	if (root == NULL)
        return;
	execute(root->left, exe_tool);
	// if (root->type == AND)
	// 	apply_and(root, exe_tool);
	// else if (root->type == OR)
	// 	apply_or(root, exe_tool);
	if (root->type == PIPE)
		apply_pipe(exe_tool);
	else if (root->type == REDIRECT_IN || root->type == HEREDOC)
		apply_redirect_in(root, exe_tool);
	else if (root->type == REDIRECT_OUT || \
			root->type == REDIRECT_APPEND)
		apply_redirect_out(root, exe_tool);
	else if (root->type == BUILTIN)
		built_in(root->command, exe_tool);
	else if (root->type == WORD)
		apply_command(root->command, exe_tool);
	execute(root->right, exe_tool);
}
