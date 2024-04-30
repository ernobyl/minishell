# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 10:19:34 by emichels          #+#    #+#              #
#    Updated: 2024/04/29 14:45:19 by emichels         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	:= minishell
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -g
HEADERS	:= 
LIBS	:= -Llibft -lft -lreadline
SRCS	:=	main.c \
			parsing.c \
			split.c \
			builtins.c \
			builtins2.c \
			run_builtin.c \
			builtin_utils.c

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@echo "Compiling minishell..."
	@make -C libft
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

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