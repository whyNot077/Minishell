/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definition.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:47:16 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/09 22:20:50 by hyojocho         ###   ########.fr       */
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

enum e_definition
{
	ERROR = -1,
	TRUE = 1,
	FALSE = 0,
	EXIST = 1,
	NOT_EXIST = -1,
	ERROR = -1,
	SUCCESS = 1
};

enum e_type
{
	SEMICOLON = 1,
	PIPE = 2,
	REDIRECT_OUT = 3,
	REDIRECT_IN = 4,
	REDIRECT_APPEND = 5,
	HEREDOC = 6,
	AND = 7,
	OR = 8,
	OPEN_PAREN = 9,
	CLOSE_PAREN = 10,
	WORD = 11
};

#endif