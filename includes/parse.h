/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:09:54 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/21 14:13:35 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "structure.h"

int				get_node_type(char **value, char **env);
t_binarytree	*parse_tokens(t_token *tokens, char **env);
void			parse_command_and_option(t_binarytree *tree, t_token *tokens,
					int *index);
int				is_redirection(int type);
void			parse_redirection(t_binarytree *tree, t_token *tokens,
					int *index);
void			parse_pipe(t_binarytree *tree, t_token *tokens, int *index);

void			parse_command(t_binarytree *tree, char *value, int type);
void			parse_option(char *value, t_tree_node *current_node);

#endif