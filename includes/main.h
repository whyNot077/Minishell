/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:07:14 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/07 17:37:56 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

char	*read_input(void);
int		check_argc(int argc, char *argv[]);
t_token	*create_token(const char *value);
int		is_operator(char c);
int		is_space(char c);
void	type_of_token(t_token *tokens, int token_index);
t_token	*create_tokens_by_lexical_analysis(const char *input);
void	free_tokens(t_token *tokens);

#endif
