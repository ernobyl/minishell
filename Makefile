# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 10:19:34 by emichels          #+#    #+#              #
#    Updated: 2024/05/15 11:04:35 by kmatjuhi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	:= minishell
CC		:= cc
# CFLAGS	:= -Wextra -Wall -Werror
HEADERS	:= 
LIBS	:= -Llibft -lft -lreadline
SRCS	:=	main.c \
			parsing/parsing.c \
			parsing/split.c \
			parsing/trim_quote.c \
			parsing/tokenize.c \
			parsing/validate_syntax.c \
			parsing/ft_strchr_next.c \
			parsing/expand_str.c \
			parsing/find_and_replace.c \
			builtins.c \
			built_in.c

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