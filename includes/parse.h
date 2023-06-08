/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:09:54 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/08 17:08:42 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "structure.h"

int				get_node_type(t_token *tokens, int index);
t_binarytree	*parse_tokens(t_token **tokens_ptr, char **env);
void			parse_command_and_option(t_binarytree *tree, t_token *tokens, \
					int *index);
int				is_redirection(int type);
void			parse_redirection(t_binarytree *tree, t_token *tokens, \
					int *index);
void			parse_pipe(t_binarytree *tree, t_token *tokens, int *index);
void			parse_command(t_binarytree *tree, char *value, int type);
void			parse_and_or(t_binarytree *tree, t_token *tokens, int *index);
t_tree_node		*find_rightmost_node(t_tree_node *node);
void			fill_command_structure(t_binarytree *tree, char *value);
int				find_pipe(t_tree_node *current);
void			replace_env_key_to_value(char **value, char **env);
char			*remove_quotes(char *value);
int				open_heredoc(t_tree_node *node);
char			*make_unique_filename(const char *previous_filename);
void			get_rightmost_and_previous(t_binarytree *tree, \
				t_tree_node **rightmost, t_tree_node **previous);
t_token			*parse_dollar_sign(t_token *tokens, int index, char **env);
void			copy_tokens_to_new_tokens(t_token *new_tokens, t_token *tokens, \
				t_token *env_tokens, size_t index);
void			put_it_on_the_top_of_the_rightmost_node(t_binarytree *tree, \
				t_tree_node *rightmost, t_tree_node *previous, \
				t_tree_node *target);
void			put_it_on_the_left_of_the_rightmost_node(t_binarytree *tree, \
				t_tree_node *rightmost, t_tree_node *previous, \
				t_tree_node *target);
void			put_it_on_the_right_of_the_rightmost_node(t_binarytree *tree, \
				t_tree_node *rightmost, t_tree_node *previous, \
				t_tree_node *target);
char			*is_str_in_the_value(char *value);

#endif