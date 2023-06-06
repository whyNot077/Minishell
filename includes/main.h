/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:07:14 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/06 16:42:06 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

char	*read_input(int display_prompt);
int		check_argc(int argc, char *argv[]);
void	init_exe_tool(t_execute *exe_tool);
void	free_everything(t_binarytree *tree, t_token *tokens, char *input);

#endif
