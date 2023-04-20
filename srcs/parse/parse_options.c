/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:19:30 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/20 16:23:44 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	parse_option(char *value, t_tree_node *current_node)
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