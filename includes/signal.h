/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:42:58 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/06 16:40:17 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

void	exec_signal(int flag);
void	exec_readline_signal(struct sigaction sa);
void	exec_parent_signal(struct sigaction sa);
void	exec_child_signal(struct sigaction sa);
void	exec_heredoc_signal(struct sigaction sa);
int		get_pid_and_signal(t_execute *exe_tool);

#endif
