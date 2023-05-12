/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:41:14 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/11 20:39:50 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_exists(const char *filename)
{
	return (access(filename, F_OK) != -1);
}

char	*get_new_filename(const char *base, int index)
{
	char	*filename;
	char	*index_str;
	char	*underscore;
	char	*base_index;

	index_str = ft_itoa(index);
	underscore = ft_strdup("_");
	base_index = ft_strjoin(base, underscore);
	filename = ft_strjoin(base_index, index_str);
	free(base_index);
	free(underscore);
	free(index_str);
	return (filename);
}

char	*make_unique_filename(const char *base)
{
	int		index;
	char	*filename;

	index = 0;
	filename = NULL;
	while (1)
	{
		filename = get_new_filename(base, index);
		if (!file_exists(filename))
			return (filename);
		index++;
		free(filename);
	}
}

static void	get_heredoc(t_tree_node *node, char *eof)
{
	char	*filename;
	int		fd;
	char	*line;

	filename = make_unique_filename(node->filename);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		node->filename = strdup("heredoc_error");
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	node->filename = filename;
	close(fd);
}

void	open_heredoc(t_tree_node *node)
{
	if (node == NULL)
	{
		return ;
	}
	open_heredoc(node->left);
	if (node->type == HEREDOC)
	{
		get_heredoc(node, node->filename);
	}
	open_heredoc(node->right);
}
