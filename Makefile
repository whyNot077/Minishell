# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 16:56:08 by minkim3           #+#    #+#              #
#    Updated: 2023/04/05 19:38:35 by minkim3          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC              = cc
CFLAGS          = -Wall -Wextra -Werror -MMD -fsanitize=address
COMFILE_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
OBJ_FLAGS = -I${HOME}/.brew/opt/readline/include
NAME            = minishell
RM              = rm -f

EXEC            = minishell
SRCS_PATH	   = ./srcs/
SRCS			= main.c
SOURCES			= $(addprefix $(SRCS_PATH), $(SRCS))
OBJECTS         = $(SOURCES:.c=.o)

HEADER_PATH     = ./includes/
S_HEADER  	    = minishell.h
HEADER			= $(addprefix $(HEADER_PATH), $(S_HEADER))

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(COMFILE_FLAGS) $(OBJECTS) -o $(EXEC)
	@echo -e "$(GREEN)$(EXEC) created!$(DEFAULT)"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
	$(RM) $(OBJECTS:.o=.d)

fclean: clean
	@$(RM) $(EXEC)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re

-include $(OBJECTS:.o=.d)

RED = \033[1;31m
PINK = \033[1;35m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
DEFAULT = \033[0m