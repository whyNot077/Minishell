/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:41:14 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/31 18:22:24 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_heredoc_from_readline(t_tree_node *node, char *eof, \
	int fd, char *filename)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, eof) == 0)
		{
			close(fd);
			free(node->filename);
			node->filename = filename;
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

static int	get_heredoc(t_tree_node *node, char *eof, int *stdin_dup)
{
	char	*filename;
	int		fd;

	filename = make_unique_filename(node->filename);
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == ERROR)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	*stdin_dup = dup(STDIN_FILENO);
	exec_signal(HEREDOE_SIG);
	return (get_heredoc_from_readline(node, eof, fd, filename));
}

int	open_heredoc(t_tree_node *node)
{
	int	stdin_dup;

	if (node == NULL)
		return (0);
	if (open_heredoc(node->left) != 0)
		return (1);
	if (node->type == HEREDOC)
	{
		if (get_heredoc(node, node->filename, &stdin_dup) == ERROR)
		{
			dup2(stdin_dup, STDIN_FILENO);
			close(stdin_dup);
			return (1);
		}
		dup2(stdin_dup, STDIN_FILENO);
		close(stdin_dup);
	}
	if (open_heredoc(node->right) != 0)
		return (1);
	return (0);
}
