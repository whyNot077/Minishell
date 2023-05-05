/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:26:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/05 20:54:30 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

void		execute(t_tree_node *root, t_execute *exe_tool);
t_execute	*envp_init(char **envp);
// pipe
void		apply_pipe(t_execute *exe_tool);
// redirection
void		open_redirect_out(t_tree_node *root, t_execute *exe_tool);
void		open_redirect_in(t_tree_node *root, t_execute *exe_tool);
void		apply_redirect_in(t_execute *exe_tool);
void		apply_redirect_out(t_execute *exe_tool);
void		restore_redirect_in(t_execute *exe_tool);
void		restore_redirect_out(t_execute *exe_tool);
// command
void		apply_command(char **args, t_execute *exe_tool);
// free
void		free_envp(t_execute *execute);

#endif