/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:42:58 by minkim3           #+#    #+#             */
/*   Updated: 2023/05/30 15:17:32 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

void	exec_signal(int flag);
void	exec_readline_signal(struct sigaction sa);
void	exec_parent_signal(struct sigaction sa);
void	exec_child_signal(struct sigaction sa);
void	exec_heredoc_signal(struct sigaction sa);

#endif
