# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emichels <emichels@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 10:19:34 by emichels          #+#    #+#              #
#    Updated: 2024/06/17 14:38:34 by emichels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME	:= minishell
CC		:= gcc
CFLAGS	:= -Wextra -Wall -Werror -g #-fsanitize=address
HEADERS	:= -I./builtins/
LIBS	:= -Llibft -lft -lreadline
SRCS	:=	main.c \
			exec/heredoc.c \
			exec/exec.c \
			exec/pipex_utils.c \
			exec/open_files.c \
			exec/fd_utils.c \
			parsing/parsing.c \
			parsing/validate_syntax.c \
			parsing/quote_utils.c \
			parsing/mod_str.c \
			parsing/split.c \
			parsing/expand_str.c \
			parsing/ft_strchr_next.c \
			parsing/trim_quote.c \
			parsing/find_and_replace.c \
			tokenize/tokenize.c \
			tokenize/list_utils.c \
			builtins/environment.c \
			builtins/builtins.c \
			builtins/builtins2.c \
			builtins/run_builtin.c \
			builtins/builtin_utils.c \
			builtins/error_handling.c \
			includes/global.c \
			exitstatus/exitstatus.c \

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