/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:30:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 19:08:17 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_node_type(char *value)
{
	if (value == NULL)
		return (ERROR);
	if (value[0] == '$')
		return (ENV);
	else if (value[0] == '-')
		return (OPTION);
	else
		return (WORD);
}

binarytree	*parse_tokens(t_token *tokens)
{
	binarytree	*tree;
	int			index;

	if (!tokens)
		return (NULL);
	tree = create_tree();
	index = 0;
	tree->root = parse_command(tokens, &index);
	return (tree);
}
