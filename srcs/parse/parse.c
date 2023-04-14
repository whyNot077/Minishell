/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:30:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 19:36:04 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Update change_env_to_word function to accept the env parameter
// static void	change_env_to_word(char **value, char **env)
// {
// 	// Your implementation for changing the environment variable to a word
// }

int	get_node_type(char *value, char **env)
{
	(void)env;
	if (value == NULL)
		return (ERROR);
	if (value[0] == '$')
	{
		// change_env_to_word(&value, env); // Pass env to the function
		return (WORD);
	}
	else if (value[0] == '-')
		return (OPTION);
	else
		return (WORD);
}

static t_tree_node	*parse_pipe_sequence(t_token *tokens, int *index, char **env)
{
	t_tree_node	*node;
	t_tree_node	*temp_node;

	node = parse_command(tokens, index, env);
	while ((size_t)(*index) < tokens->token_count \
		&& tokens[*index].type == PIPE)
	{
		temp_node = create_new_node(&tokens[*index]);
		temp_node->type = tokens[*index].type;
		(*index)++;
		temp_node->left = node;
		temp_node->right = parse_command(tokens, index, env);
		node = temp_node;
	}
	return (node);
}

t_binarytree	*parse_tokens(t_token *tokens, char **env)
{
	t_binarytree *tree;
	int index;

	if (!tokens)
		return (NULL);
	tree = create_tree();
	index = 0;
	tree->root = parse_pipe_sequence(tokens, &index, env);
	return (tree);
}