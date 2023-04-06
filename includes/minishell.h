/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:35:37 by minkim3           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/06 19:16:27 by hyojocho         ###   ########.fr       */
=======
/*   Updated: 2023/04/06 18:58:34 by minkim3          ###   ########.fr       */
>>>>>>> 92fb2a32712ab212e5c6520dce4f8c4a34a8f78f
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parsing.h"
# include "execute.h"
<<<<<<< HEAD
# include "built_in.h"
=======
# include "binary_tree.h"
# include "structure.h"
>>>>>>> 92fb2a32712ab212e5c6520dce4f8c4a34a8f78f

# define RED "\033[1;31m"
# define PINK "\033[1;35m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define DEFAULT "\033[0m"

#endif