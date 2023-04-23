/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definition.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:47:16 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/22 16:44:54 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITION_H
# define DEFINITION_H

# define RED "\033[1;31m"
# define PINK "\033[1;35m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define DEFAULT "\033[0m"

# define MAX_INPUT_SIZE 1024
# define MAX_TOKENS 64

enum	e_definition
{
	ERROR = -1,
	SUCCESS = 1,
	TRUE = 1,
	FALSE = 0,
	EXIST = 1,
	NOT_EXIST = -1
};

/*
** PIPE = |
** REDIRECT_OUT = >
** REDIRECT_IN = <
** REDIRECT_APPEND = >>
** HEREDOC = <<
** AND = &&
** OR = ||
*/

enum	e_type
{
	PIPE = 1,
	REDIRECT_OUT = 2,
	REDIRECT_IN = 3,
	REDIRECT_APPEND = 4,
	HEREDOC = 5,
	AND = 6,
	OR = 7,
	WORD = 8,
	BUILTIN = 9
};

#endif