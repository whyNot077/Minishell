/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options_or_arguments.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:09:00 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/23 21:55:02 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	get_command_size(t_tree_node *command_node)
{
	size_t	i;

	i = 0;
	while (command_node->command[i] != NULL)
	{
		i++;
	}
	return (i);
}

static char	**get_new_command(t_tree_node *command_node, \
	char *value, size_t size)
{
	char	**new_command;

	new_command = ft_calloc(size + 2, sizeof(char *));
	ft_memmove(new_command, command_node->command, size * sizeof(char *));
	new_command[size] = value;
	new_command[size + 1] = NULL;
	return (new_command);
}

void	fill_command_structure(t_binarytree *tree, char *value)
{
	char		**new_command;
	t_tree_node	*command_node;
	size_t		size;

	command_node = find_rightmost_node(tree->root);
	if (command_node->command == NULL)
	{
		command_node->command = (char **)ft_calloc(2, sizeof(char *));
		command_node->command[0] = value;
		command_node->command[1] = NULL;
	}
	else
	{
		size = get_command_size(command_node);
		new_command = get_new_command(command_node, value, size);
		free(command_node->command);
		command_node->command = new_command;
	}
}
