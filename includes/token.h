/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:02:22 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/07 21:52:28 by minkim3          ###   ########.fr       */
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
void	free_tokens(t_token **tokens_ptr);

#endif