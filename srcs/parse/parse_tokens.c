/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:30:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/17 20:13:17 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_redirection_out(char *value)
{
	if (value == NULL)
		return (0);
	if (ft_strcmp(value, ">") == 0)
		return (1);
	else if (ft_strcmp(value, ">>") == 0)
		return (1);
	return (0);
}

static int	is_redirection_in(char *value)
{
	if (value == NULL)
		return (0);
	if (ft_strcmp(value, "<") == 0)
		return (1);
	else if (ft_strcmp(value, "<<") == 0)
		return (1);
	return (0);
}

static void	parse_command(t_binarytree *tree, char *value, int type)
{
	t_tree_node	*new_node;
	t_tree_node	*current_node;

	current_node = tree->current_node;
	new_node = create_new_node(value, type);
	if (current_node == NULL)
		tree->root = new_node;
	else if (is_redirection_in(current_node->data))
		current_node->right = new_node;
	else if (is_redirection_out(current_node->data))
		current_node->left = new_node;
	else if (current_node->left == NULL)
		current_node->left = new_node;
	else
		current_node->right = new_node;
	tree->current_node = new_node;
}

/* 
** If it is a redirection, put it in the parent of the current tree node.
** so that the current tree node is the right child of the redirection node.
*/

static void	parse_redirection_out(t_binarytree *tree, char *value, int type)
{
	t_tree_node	*new_node;
	t_tree_node	*current_node;

	current_node = tree->current_node;
	new_node = create_new_node(value, type);
	if (current_node == tree->root)
	{
		tree->root = new_node;
	}
	tree->current_node = new_node;
	new_node->left = current_node;
}

/* command and option */
static void	parse_command_and_option(t_binarytree *tree, t_token *tokens,
		int *index, char **env)
{
	char	*value;
	int		type;

	value = tokens[(*index)].value;
	type = tokens[(*index)].type;
	parse_command(tree, value, type);
	if (get_node_type(&tokens[(*index) + 1].value, env) == OPTION)
	{
		(*index)++;
		value = tokens[(*index)].value;
		tree->current_node->option = value;
	}
}

/* outfile to the current-> right child*/
static void	parse_outfile(t_binarytree *tree, char *value, int type)
{
	t_tree_node	*new_node;
	t_tree_node	*current_node;

	current_node = tree->current_node;
	new_node = create_new_node(value, type);
	if (new_node->type != WORD)
		printf("syntax error\n");
	else
		current_node->right = new_node;
	tree->current_node = new_node;
}

static void	parse_tree(t_binarytree *tree, t_token *tokens, int *index,
		char **env)
{
	char	*value;
	char	*next_value;
	int		type;

	value = tokens[(*index)].value;
	type = tokens[(*index)].type;
	next_value = tokens[(*index) + 1].value;
	if (type == WORD)
	{
		parse_command_and_option(tree, tokens, index, env);
		if (is_redirection_out(tokens[(*index) + 1].value))
		{
			(*index)++;
			parse_redirection_out(tree, tokens[(*index)].value,
					tokens[(*index)].type);
			(*index)++;
			parse_outfile(tree, tokens[(*index)].value, tokens[(*index)].type);
		}
	}
}

t_binarytree	*parse_tokens(t_token *tokens, char **env)
{
	t_binarytree *tree;
	int index;

	if (!tokens)
		return (NULL);
	tree = create_tree();
	index = 0;
	while (index < (int)tokens->token_count)
	{
		get_node_type(&tokens[index].value, env);
		parse_tree(tree, tokens, &index, env);
		index++;
	}
	return (tree);
}