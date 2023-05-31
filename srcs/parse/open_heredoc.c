/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:41:14 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/31 16:16:03 by minkim3          ###   ########.fr       */
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

char	*make_unique_filename(const char *previous_filename)
{
	int		index;
	char	*filename;

	index = 0;
	filename = NULL;
	while (1)
	{
		filename = get_new_filename(previous_filename, index);
		if (!file_exists(filename))
		{
			free((void *)previous_filename);
			return (filename);
		}
		index++;
		free(filename);
	}
}

static int	get_heredoc(t_tree_node *node, char *eof, int *stdin_dup)
{
	char	*filename;
	int		fd;
	char	*line;

	filename = make_unique_filename(node->filename);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == ERROR)
	{
		perror("open");
		exit(1);
	}
	*stdin_dup = dup(STDIN_FILENO);
	exec_signal(HEREDOE_SIG);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, eof) == 0)
		{
			dup2(*stdin_dup, STDIN_FILENO);
			close(*stdin_dup);
			node->filename = filename;
			close(fd);
			if (line == NULL)
				return (ERROR);
			free(line);
			return (0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	open_heredoc(t_tree_node *node)
{
	int stdin_dup;

	if (node == NULL)
		return (0);
	if (open_heredoc(node->left) != 0)
		return (1);
	if (node->type == HEREDOC)
	{
		if (get_heredoc(node, node->filename, &stdin_dup) == ERROR)
		{
			printf("close error\n");
			return (1);
		}
	}
	if (open_heredoc(node->right) != 0)
		return (1);
	return (0);
}