/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_and_option.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:08:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/23 19:40:40 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
** find the rightmost node and return it.
*/
t_tree_node *find_rightmost_node(t_tree_node *node)
{
    if (node == NULL)
    {
        return NULL;
    }

    while (node->right)
    {
        node = node->right;
    }

    return node;
}

void	add_options_or_arguments_to_the_tree(t_binarytree *tree, char *value)
{
	char	**new_command;
	t_tree_node *command_node;
	size_t i;
	size_t j;
	size_t k;

	command_node = find_rightmost_node(tree->root);
	if (command_node->command == NULL)
	{
		command_node->command = (char **)ft_calloc(2, sizeof(char *));
		command_node->command[0] = value;
		command_node->command[1] = NULL;
	}
	else
	{
		i = 0;
		while (command_node->command[i] != NULL)
		{
			i++;
		}
		new_command = (char **)calloc(i + 2, sizeof(char *));
		j = 0;
		k = 0;
		while (j < i)
		{
			new_command[k] = command_node->command[j];
			j++, k++;
		}
		new_command[k] = value;
		new_command[k + 1] = NULL;
		free(command_node->command);
		command_node->command = new_command;
	}
}

/*
** if the tree is empty, add the command node to the root
** else, find the rightmost node.
** If the rightmost node is of type WORD, BUILTIN return ;
** else, store the previous rightmost node as the left child of the new command node,
** and the command node should be rightmost node.
*/
void add_command_to_the_tree(t_binarytree *tree, t_tree_node *command_node)
{
    t_tree_node *current;
    t_tree_node *previous;

    if (tree->root == NULL)
    {
        tree->root = command_node;
		return ;
    }
    else
    {
        current = tree->root;
        previous = NULL;
        while (current->right)
        {
            previous = current;
            current = current->right;
        }
        if (current->type == WORD || current->type == BUILTIN)
        {
            return;
        }
        command_node->left = current;
        if (previous)
        {
            previous->right = command_node;
        }
        else
        {
            tree->root = command_node;
        }
    }
}



void	parse_command_and_option(t_binarytree *tree, t_token *tokens,
		int *index)
{
	t_tree_node *command_node;

	command_node = create_new_node(tokens[*index].value, tokens[*index].type);
	add_command_to_the_tree(tree, command_node);
	while (tokens[*index].type == WORD || tokens[*index].type == BUILTIN)
	{
		add_options_or_arguments_to_the_tree(tree, tokens[*index].value);
		(*index)++;
	}
}