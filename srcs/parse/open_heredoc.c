/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:41:14 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/09 19:17:52 by minkim3          ###   ########.fr       */
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

char	*get_dir_route(const char *base)
{
	char	*dir;
	char	*dir_base;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("getcwd() error");
		exit(1);
	}
	dir = ft_strjoin(cwd, "/tmp/");
	dir_base = ft_strjoin(dir, base);
	free(dir);
	return (dir_base);
}
char	*make_unique_filename(const char *base)
{
	int		index;
	char	*filename;
	char	*dir_base;

	index = 0;
	filename = NULL;
	dir_base = get_dir_route(base);
	while (1)
	{
		filename = get_new_filename(dir_base, index);
		if (!file_exists(filename))
		{
			free(dir_base);
			return (filename);
		}
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
		printf("open error\n");
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, eof) == 0)
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
