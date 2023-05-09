# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 16:56:08 by minkim3           #+#    #+#              #
#    Updated: 2023/05/09 16:02:48 by minkim3          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC              = cc
CFLAGS          = -Wall -Wextra -Werror -MMD
# CFLAGS          = -Wall -Wextra -Werror -MMD -fsanitize=address
COMFILE_FLAGS   = -lreadline -L${HOME}/.brew/opt/readline/lib
OBJ_FLAGS       = -I${HOME}/.brew/opt/readline/include
NAME            = minishell
RM              = rm -f

P_LIBFT			= ./libft/
A_LIBFT         = libft.a
LIBFT			= $(addprefix $(P_LIBFT), $(A_LIBFT))

EXEC            = minishell
SRCS_PATH       = ./srcs/

MAIN_PATH  	    = ./main/
MAIN_SRCS       = main.c read_input.c check_argc.c error.c
MAIN            = $(addprefix $(MAIN_PATH), $(MAIN_SRCS))

SIGNAL_PATH     = ./signal/
SIGNAL_SRCS     = signal.c
SIGNAL          = $(addprefix $(SIGNAL_PATH), $(SIGNAL_SRCS))

TOKEN_PATH    = ./token/
TOKEN_SRCS    = token.c lexical_analysis.c special_tokens.c special_tokens2.c \
				handle_quotes.c read_input_until_finding_the_quote.c \
				process_input.c space_token.c
TOKEN         = $(addprefix $(TOKEN_PATH), $(TOKEN_SRCS))

PARSE_PATH     = ./parse/
PARSE_SRCS     = parse_tokens.c get_node_type.c parse_command_and_option.c\
				 parse_pipe.c parse_redirection.c parse_and_or.c \
				 parse_options_or_arguments.c replace_env_key_to_value.c \
				 remove_quotes.c open_heredoc.c
PARSE          = $(addprefix $(PARSE_PATH), $(PARSE_SRCS))

UTILS_PATH      = ./data_structure/
UTILS_SRCS      = display.c dynamic_array.c binary_tree.c arraylist.c
UTILS           = $(addprefix $(UTILS_PATH), $(UTILS_SRCS))

EXECUTE_PATH    = ./execute/
EXECUTE_SRCS    = execute.c envp_init.c\
					./pipe/pipe_apply.c ./pipe/pipe_open.c\
					./redirection/redirection_apply.c ./redirection/redirection_open.c \
					child_process.c parent_process.c\
					command_apply.c
EXECUTE         = $(addprefix $(EXECUTE_PATH), $(EXECUTE_SRCS))

BUILT_IN_PATH    = ./built_in/
BUILT_IN_SRCS    = built_in.c echo.c ./export/export.c ./export/export_get_env.c\
					./export/export_print.c ./export/export_arg_validate.c\
					./unset/unset.c ./unset/unset_apply.c\
					env.c pwd.c command_exit.c\
					./cd/cd.c ./cd/chdir_check.c ./cd/get_value.c
BUILT_IN         = $(addprefix $(BUILT_IN_PATH), $(BUILT_IN_SRCS))

SOURCES         = $(addprefix $(SRCS_PATH), $(MAIN))\
				  $(addprefix $(SRCS_PATH), $(TOKEN))\
				  $(addprefix $(SRCS_PATH), $(SIGNAL))\
				  $(addprefix $(SRCS_PATH), $(PARSE))\
				  $(addprefix $(SRCS_PATH), $(UTILS))\
				  $(addprefix $(SRCS_PATH), $(EXECUTE))\
				  $(addprefix $(SRCS_PATH), $(BUILT_IN))

OBJECTS         = $(SOURCES:.c=.o)

HEADER_PATH     = ./includes/
S_HEADER        = minishell.h
HEADER          = $(addprefix $(HEADER_PATH), $(S_HEADER))

RED             = \033[1;31m
PINK            = \033[1;35m
GREEN           = \033[1;32m
YELLOW          = \033[1;33m
BLUE            = \033[1;34m
DEFAULT         = \033[0m

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(P_LIBFT)
	@$(CC) $(CFLAGS) $(COMFILE_FLAGS) $(OBJECTS) $(LIBFT) -o $(EXEC)
	@echo -e "$(GREEN)create $(EXEC)!$(DEFAULT)"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJECTS)
	@$(RM) $(OBJECTS:.o=.d)
	@make clean -C $(P_LIBFT)
	@echo -e "$(PINK)delete object files!$(DEFAULT)"

fclean: clean
	@$(RM) $(EXEC) $(LIBFT)
	@echo -e "$(YELLOW)delete all!$(DEFAULT)"

re:
	@make fclean
	@make all

norm:
	norminette -R CheckDefine

.PHONY: all clean fclean re norm

-include $(OBJECTS:.o=.d)
