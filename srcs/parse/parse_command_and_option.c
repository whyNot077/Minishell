/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_and_option.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:08:19 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/18 19:17:00 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(int type)
{
	return (type == REDIRECT_OUT || \
			type == REDIRECT_IN || type == REDIRECT_APPEND);
}

void	parse_command(t_binarytree *tree, char *value, int type)
{
	t_tree_node	*new_node;
	t_tree_node	*current_node;
	t_tree_node *redirection_node;

	current_node = tree->current_node;
	new_node = create_new_node(value, type);
	if (tree->root == NULL)
		tree->root = new_node;
	else
	{
		new_node->parent = current_node;
		if (current_node->type == PIPE)
			current_node->right = new_node;
		else if (is_redirection(current_node->type))
		{
			redirection_node = current_node;
			while (current_node->left != NULL)
			{
				current_node = current_node->left;
				new_node->parent = current_node;
			}
			current_node->left = new_node;
			tree->current_node = redirection_node;
			return ; 
		}
		else
		{
			while (current_node->left != NULL)
			{
				current_node = current_node->left;
				new_node->parent = current_node;
			}
			current_node->left = new_node;
		}
	}
	tree->current_node = new_node;
}

static int	option_exists(char *options, char option)
{
	int	i;

	i = 0;
	while (options[i])
	{
		if (options[i] == option)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void	add_option(char *new_option, t_tree_node *current_node)
{
	size_t	new_options_length;
	char	*new_options;

	new_options_length = ft_strlen(current_node->options)
		+ ft_strlen(new_option);
	new_options = (char *)ft_calloc(new_options_length + 1, sizeof(char));
	ft_strlcpy(new_options, current_node->options, new_options_length + 1);
	ft_strlcat(new_options, new_option, new_options_length + 1);
	free(current_node->options);
	current_node->options = new_options;
}

static void	parse_option(char *value, t_tree_node *current_node)
{
	char	*new_option;
	int		i;

	if (current_node->options == NULL)
		current_node->options = ft_strdup(value);
	else
	{
		new_option = strchr(value, '-') + 1;
		i = 0;
		while (new_option[i])
		{
			if (option_exists(current_node->options, new_option[i]) == FALSE)
				add_option(new_option, current_node);
			i++;
		}
	}
	value = current_node->options;
}

void	parse_command_and_option(t_binarytree *tree, t_token *tokens,
		int *index)
{
	t_tree_node	*current_node;

	current_node = tree->current_node;
	if (tokens[*index].type == WORD || tokens[*index].type == BUILTIN)
	{
		parse_command(tree, tokens[*index].value, tokens[*index].type);
		current_node = tree->current_node;
		(*index)++;
	}
	while ((size_t)*index < tokens->token_count
		&& tokens[*index].type == OPTION)
	{
		parse_option(tokens[*index].value, current_node);
		(*index)++;
	}
	if (tokens[*index].type == WORD || tokens[*index].type == BUILTIN)
		parse_command_and_option(tree, tokens, index);
}
