# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 10:19:34 by emichels          #+#    #+#              #
#    Updated: 2024/05/17 10:27:17 by emichels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	:= minishell
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -g
HEADERS	:= -I./builtins/
LIBS	:= -Llibft -lft -lreadline
SRCS	:=	main.c \
			parsing.c \
			split.c \
			builtins/builtins.c \
			builtins/builtins2.c \
			builtins/run_builtin.c \
			builtins/builtin_utils.c \
			builtins/environment.c \
			builtins/error_handling.c

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