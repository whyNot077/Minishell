/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:26:23 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/09 12:42:02 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

void		execute(t_tree_node *root, t_execute *exe_tool);
void		check_exceptions(t_tree_node *root, t_execute *exe_tool);
t_execute	*envp_init(char **envp);
void		infile_error(t_tree_node *root, t_execute *exe_tool);
// pipe
void		open_pipe(t_execute *exe_tool);
void		apply_built_in_pipe(char **args, t_execute *exe_tool);
// redirection
void		open_redirect_out(t_tree_node *root, t_execute *exe_tool);
void		open_redirect_in(t_tree_node *root, t_execute *exe_tool);
void		apply_redirect_in(t_execute *exe_tool);
void		apply_redirect_out(t_execute *exe_tool);
void		restore_redirect_in(t_execute *exe_tool);
void		restore_redirect_out(t_execute *exe_tool);
void		open_redirect_append(t_tree_node *root, t_execute *exe_tool);
// command
void		apply_command(char **args, t_execute *exe_tool);
void		execute_command(char *full_path, char **args, t_execute *exe_tool);
int			validate_commands(char **args, char **full_path, \
				t_execute *exe_tool);
void		apply_or(t_execute *exe_tool);
void		apply_and(t_execute *exe_tool);
// process
void		child_process(char *full_path, char **args, t_execute *exe_tool);
void		parent_process(t_execute *exe_tool);
// get path
char		**get_paths(char **envp);
// free
void		free_envp(t_execute *execute);

#endif