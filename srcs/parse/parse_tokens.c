/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choihyojong <choihyojong@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:30:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/26 23:36:18 by choihyojong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_tree(t_binarytree *tree, t_token *tokens, int *index)
{
	// char	*value;
	int		type;
	int		token_count;

	token_count = tokens->token_count;
	while (*index < token_count)
	{
		// value = tokens[*index].value;
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
			return ;
	}
}

t_binarytree	*parse_tokens(t_token *tokens, char **env)
{
	t_binarytree	*tree;
	int				index;

	index = 0;
	if (!tokens)
		return (NULL);
	tree = create_tree();
	while ((size_t)index < tokens->token_count)
	{
		if (tokens[index].type == WORD)
			tokens[index].type = get_node_type(tokens, index, env);
		index++;
	}
	index = 0;
	parse_tree(tree, tokens, &index);
	open_heredoc(tree->root);
	return (tree);
}
