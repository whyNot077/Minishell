/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choihyojong <choihyojong@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:09:38 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/28 02:05:51 by choihyojong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
# define MAX_INPUT_SIZE 1024
# include "minishell.h"

typedef struct s_arraylist
{
	int					count;
	int					size;
	char				**data;
}						t_arraylist;

typedef struct s_execute
{
	char				*infile_str;
	char				*outfile_str;
	char				**paths;
	int					curr_pipe_flag;
	int					pipe_flag;
	int					exit_flag;
	int					built_in_flag;
	int					prev_fd;
	int					infile_fd;
	int					outfile_fd;
	int					dup_tmp;
	int					pipe_fd[2];
	pid_t				pid;
	t_arraylist			*env;
	t_arraylist			*export;
}						t_execute;

typedef struct s_token
{
	char				*value;
	int					type;
	size_t				token_count;
}						t_token;

typedef struct array_type
{
	size_t				max_count;
	size_t				token_count;
	t_token				*token;
}						t_array;

typedef struct s_process_input_data
{
	const char			*input;
	t_token				*tokens;
	t_array				*list;
	char				buffer[MAX_INPUT_SIZE];
	int					buffer_index;
}						t_process_input_data;

typedef struct s_find
{
	char				quote_char;
	int					*find;
}						t_find;

typedef struct tree_node
{
	char				*value;
	char				**command;
	char				*filename;
	int					type;
	struct tree_node	*left;
	struct tree_node	*right;
}						t_tree_node;

typedef struct binarytree
{
	t_tree_node			*root;
	int					heredoc_count;
	int					syntex_error;
}						t_binarytree;

#endif