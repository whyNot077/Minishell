/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:16:53 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 21:23:05 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_tree(tree_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == WORD || node->type == ENV || node->type == OPTION)
	{
		printf("Executing: %s\n", node->data);
	}
	else if (node->type == PIPE)
		printf("PIPE = %s\n", node->data);
	else if (node->type == REDIRECT_OUT)
		printf("REDIRECT_OUT = %s\n", node->data);
	else if (node->type == REDIRECT_IN)
		printf("REDIRECT_IN = %s\n", node->data);
	display_tree(node->left);
	display_tree(node->right);
}