# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 10:19:34 by emichels          #+#    #+#              #
#    Updated: 2024/07/11 17:21:50 by kmatjuhi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME	:= minishell
CC		:= gcc
CFLAGS	:= -Wextra -Wall -Werror -g -fsanitize=address
HEADERS	:= -I./builtins/
LIBS	:= -Llibft -lft -lreadline
SRCS	:=	main.c \
			exec/child.c \
			exec/exec_error.c \
			exec/exec.c \
			exec/heredoc.c \
			exec/fd_utils.c \
			exec/open_files.c \
			exec/open_files2.c \
			exec/pipex_utils.c \
			exec/safe_func.c \
			parsing/add_space.c \
			parsing/expand_str.c \
			parsing/expand_str2.c \
			parsing/parsing_utils.c \
			parsing/parsing.c \
			parsing/quote_utils.c \
			parsing/split.c \
			parsing/trim_quote.c \
			parsing/validate_syntax.c \
			tokenize/tokenize.c \
			tokenize/list_utils.c \
			builtins/builtin_utils.c \
			builtins/builtin_utils2.c \
			builtins/builtins.c \
			builtins/builtins2.c \
			builtins/environment.c \
			builtins/error_handling.c \
			builtins/get_builtin_num.c \
			builtins/run_builtin.c \

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@echo "Compiling minishell..."
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJS)
	@make clean -C libft

fclean: clean
	@echo "Cleaning everything else..."
	@rm -rf $(NAME)
	@make fclean -C libft

re: clean all

.PHONY: all, clean, fclean, re