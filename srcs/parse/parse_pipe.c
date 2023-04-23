/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:39:42 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/23 19:39:45 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** If the tree is empty, print syntax error
** else, find the rightmost node.
** If the rightmost node is of type WORD, BUILTIN.
** move to the left, while the type of the node is redirection.
** else, print syntax error
*/
static void pipe_to_the_tree(t_binarytree *tree, t_tree_node *pipe_node, int *index)
{
    t_tree_node *current;

    if (tree->root == NULL)
    {
		free(pipe_node);
        printf("Syntax error: unexpected pipe '|'\n");
        return;
    }
    else
    {
        current = find_rightmost_node(tree->root);

        if (current->type == WORD || current->type == BUILTIN)
        {
            while (current->left && is_redirection(current->left->type))
            {
                current = current->left;
            }
			if (current->left && current->left->type == PIPE)
				printf("Syntax error: unexpected pipe '|'\n");
            pipe_node->left = current->left;
            current->left = pipe_node;
        }
        else
        {
			free(pipe_node);
            printf("Syntax error: unexpected pipe '|'\n");
            return;
        }
    }
    (*index)++;
}

void	parse_pipe(t_binarytree *tree, t_token *tokens, int *index)
{
	int			type;
	char		*pipe;
	t_tree_node	*pipe_node;

	type = tokens[*index].type;
	pipe = tokens[*index].value;
	if (type != PIPE)
		return ;
	pipe_node = create_new_node(pipe, type);
	pipe_to_the_tree(tree, pipe_node, index);
}
