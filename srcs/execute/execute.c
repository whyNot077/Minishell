/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:02:24 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/30 21:14:39 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(t_binarytree *tree, t_execute *exe_tool)
{
	execute(tree->root->left, exe_tool);
	if (tree->root == NULL)
        return;
	// if (tree->root->type == AND)
	// 	apply_and(tree->root, exe_tool);
	// else if (tree->root->type == OR)
	// 	apply_or(tree->root, exe_tool);
	else if (tree->root->type == PIPE)
		apply_pipe(tree->root, exe_tool);
	// else if (tree->root->type == REDIRECT_IN || tree->root->type == HEREDOC)
	// 	apply_redirect_in(tree->root, exe_tool);
	// else if (tree->root->type == REDIRECT_OUT || \
	// 		tree->root->type == REDIRECT_APPEND)
	// 	apply_redirect_out(tree->root, exe_tool);
	else if (tree->root->type == BUILTIN)
		built_in(tree->root->command, exe_tool);
	// else if (tree->root->type == WORD)
	// 	apply_command(tree->root->command, exe_tool);
	// execute(tree->root->right, exe_tool);
}
