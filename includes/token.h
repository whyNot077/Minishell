/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:02:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/08 16:11:56 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "structure.h"

t_token	*create_token(const char *value);
int		is_operator(char c);
int		is_space(char c);
void	type_of_token(t_token *tokens, int token_index);
t_token	*create_tokens_by_lexical_analysis(const char *input);
t_token	*special_tokens(t_token *tokens, int token_index);
int		is_special_token(char *token);
int		is_quote_char(char c);
int		is_backslash(char c);
void	handle_quotes(const char *input, int *i, char *buffer,
			int *buffer_index);
int		num_of_special_tokens(t_token *tokens, int token_index);
void	free_tokens(t_token **tokens_ptr);

#endif