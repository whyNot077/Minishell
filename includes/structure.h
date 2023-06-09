/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:09:38 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/09 12:22:50 by minkim3          ###   ########.fr       */
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
	int					open_error;
	int					open_error_for_and_or;
	int					stop;
	int					num_of_executed_commands;
	pid_t				pid;
	pid_t				last_pid;
	t_arraylist			*env;
	t_arraylist			*export;
}						t_execute;

typedef struct s_token
{
	char				*value;
	int					type;
	int					syntax_error;
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
	int					syntex_error;
}						t_binarytree;

#endif