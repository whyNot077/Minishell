/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:12:33 by hyojocho          #+#    #+#             */
/*   Updated: 2023/04/26 13:47:11 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

// built_in
void	built_in(char **args, t_execute *execute);
// built_in_commands
// echo
void	echo(char **args, t_execute *execute);
// export
void	export(char **args, t_arraylist *envp, t_arraylist *export, \
				int outfile_fd);
void	get_args_to_envp(char **args, t_arraylist *envp, t_arraylist *export);
void	print_export(t_arraylist *envp, int outfile_fd);
int		validate_key_args(char **args, int args_idx);
int		check_same_key(char *str, t_arraylist *envp);
// unset
void	unset(char **args, t_arraylist *env, t_arraylist *export);
void	apply_unset(char *str, t_arraylist *env, t_arraylist *export);
// env
void	env(t_arraylist *envp, int outfile_fd);
// pwd
void	pwd(void);
// exit
void	command_exit(char **args);
// cd
void	cd(char **args, t_execute *execute);
int		validate_chdir(char **args, char *pwd_value);
char	*get_target_value(char *str, t_arraylist *envp);
int		get_env_value(char *str, t_arraylist *envp);

#endif