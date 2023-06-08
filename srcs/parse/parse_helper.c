/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:45:00 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/08 16:52:53 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_it_on_the_left_of_the_rightmost_node(t_binarytree *tree, \
	t_tree_node *rightmost, t_tree_node *previous, t_tree_node *target)
{
	(void)tree;
	(void)previous;
	target->left = rightmost->left;
	rightmost->left = target;
}

void	put_it_on_the_right_of_the_rightmost_node(t_binarytree *tree, \
	t_tree_node *rightmost, t_tree_node *previous, t_tree_node *target)
{
	(void)tree;
	(void)previous;
	rightmost->right = target;
}

void	put_it_on_the_top_of_the_rightmost_node(t_binarytree *tree, \
	t_tree_node *rightmost, t_tree_node *previous, t_tree_node *target)
{
	target->left = rightmost;
	if (previous)
		previous->right = target;
	else
		tree->root = target;
}

t_tree_node	*find_rightmost_node(t_tree_node *node)
{
	if (node == NULL)
		return (NULL);
	while (node->right)
		node = node->right;
	return (node);
}

int	find_pipe(t_tree_node *current)
{
	t_tree_node	*dummy;

	dummy = current;
	while (dummy)
	{
		if (dummy->type == PIPE)
		{
			return (TRUE);
		}
		dummy = dummy->left;
	}
	return (FALSE);
}
