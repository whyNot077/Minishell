# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 16:56:08 by minkim3           #+#    #+#              #
#    Updated: 2023/04/06 15:29:05 by minkim3          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC              = cc
CFLAGS          = -Wall -Wextra -Werror -MMD -fsanitize=address
COMFILE_FLAGS   = -lreadline -L${HOME}/.brew/opt/readline/lib
OBJ_FLAGS       = -I${HOME}/.brew/opt/readline/include
NAME            = minishell
RM              = rm -f

EXEC            = minishell
SRCS_PATH       = ./srcs/
SRCS            = main.c

PARSING_PATH    = ./parsing/
PARSING_SRCS    = init.c
PARSING         = $(addprefix $(PARSING_PATH), $(PARSING_SRCS))

UTILS_PATH    = ./utils/
UTILS_SRCS    = linked_list.c\
				destroy.c
UTILS         = $(addprefix $(UTILS_PATH), $(UTILS_SRCS))

EXECUTE_PATH    = ./execute/
EXECUTE_SRCS    = execute.c
EXECUTE         = $(addprefix $(EXECUTE_PATH), $(EXECUTE_SRCS))

SOURCES         = $(addprefix $(SRCS_PATH), $(SRCS))\
				  $(addprefix $(SRCS_PATH), $(PARSING))\
				  $(addprefix $(SRCS_PATH), $(UTILS))\
				  $(addprefix $(SRCS_PATH), $(EXECUTE))

OBJECTS         = $(SOURCES:.c=.o)

HEADER_PATH     = ./includes/
S_HEADER        = minishell.h\
				  linked_list.h
HEADER          = $(addprefix $(HEADER_PATH), $(S_HEADER))

RED             = \033[1;31m
PINK            = \033[1;35m
GREEN           = \033[1;32m
YELLOW          = \033[1;33m
BLUE            = \033[1;34m
DEFAULT         = \033[0m

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(COMFILE_FLAGS) $(OBJECTS) -o $(EXEC)
	@echo -e "$(GREEN)create $(EXEC)!$(DEFAULT)"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJECTS)
	@$(RM) $(OBJECTS:.o=.d)
	@echo -e "$(BLUE)delete object files!$(DEFAULT)"

fclean: clean
	@$(RM) $(EXEC)
	@echo -e "$(PINK)delete all!$(DEFAULT)"

re:
	@make fclean
	@make all

norm:
	norminette -R CheckDefine

.PHONY: all clean fclean re norm

-include $(OBJECTS:.o=.d)
