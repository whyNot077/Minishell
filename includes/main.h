/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:07:14 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/14 15:47:38 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

char	*read_input(int display_prompt);
void	handle_readline(char *input);
int		check_argc(int argc, char *argv[]);
void	error_exit(char *message);

#endif
