/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:30:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/07 12:05:43 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parse_tree(t_binarytree *tree, t_token *tokens, int *index)
{
	int	type;
	int	token_count;

	token_count = tokens->token_count;
	while (*index < token_count)
	{
		type = tokens[*index].type;
		if (type == WORD || type == BUILTIN)
			parse_command_and_option(tree, tokens, index);
		else if (is_redirection(type))
			parse_redirection(tree, tokens, index);
		else if (type == PIPE)
			parse_pipe(tree, tokens, index);
		else if (type == AND || type == OR)
			parse_and_or(tree, tokens, index);
		if (tree->syntex_error == TRUE)
			return (ERROR);
	}
	return (0);
}

static int	fill_tree(t_binarytree *tree, t_token *tokens)
{
	int	index;

	index = 0;
	if (parse_tree(tree, tokens, &index) == ERROR)
	{
		destroy_tree(&tree);
		return (ERROR);
	}
	if (open_heredoc(tree->root) != 0)
	{
		destroy_tree(&tree);
		return (ERROR);
	}
	return (0);
}

static t_token	*finalize_token(t_token *tokens, char **env)
{
	int	index;

	index = 0;
	while ((size_t)index < tokens->token_count)
	{
		if (tokens[index].type == WORD)
		{
			tokens[index].type = get_node_type(tokens, index);
			if (tokens[index].type == WORD)
			{
				tokens = parse_dollar_sign(tokens, index, env);
				if (tokens == NULL)
					return (NULL);
			}
		}
		index++;
	}
	return (tokens);
}

t_binarytree	*parse_tokens(t_token **tokens_ptr, char **env)
{
	t_binarytree	*tree;
	int				index;
	t_token			*tokens;

	tokens = *tokens_ptr;
	if (!tokens)
		return (NULL);
	tree = create_tree();
	index = 0;
	*tokens_ptr = finalize_token(tokens, env);
	if (fill_tree(tree, *tokens_ptr) == ERROR)
		return (NULL);
	return (tree);
}
