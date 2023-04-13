/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:09:54 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/13 20:52:59 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "structure.h"

int			get_node_type(char *value);
tree_node	*parse_command(t_token *tokens, int *index);
tree_node	*parse_pipe(t_token *tokens, int *index);
tree_node	*parse_redirect(t_token *tokens, int *index);
binarytree	*parse_tokens(t_token *tokens);
tree_node	*parse_commands(t_token *tokens, int *index);
#endif