/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/04/22 11:50:43 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <errno.h>

volatile sig_atomic_t	exit_flag = 0;

void	handle_signal(int sig)
{
	if (sig == SIGQUIT || sig == SIGHUP || sig == SIGTERM)
		exit_flag = 1;
	else if (sig == SIGINT)
		write(1, "\nhandle signal interrupt\n", 25);
}

void	double_buf_size(char *str, size_t buf_size)
{
	if (errno == ERANGE)
	{
		buf_size *= 2;
		free(str);
	}
	else
	{
		perror("pwd: getcwd failed");
		free(str);
		return ;
	}
}

void	pwd_builtin(void)
{
	size_t	buf_size;
	char	*cwd;

	buf_size = 256;
	cwd = NULL;
	cwd = malloc(buf_size);
	if (cwd == NULL)
	{
		perror("malloc failed");
		return ;
	}
	if (getcwd(cwd, buf_size) != NULL)
	{
		printf("%s\n", cwd);
		free(cwd);
		return ;
	}
	else
	{
		double_buf_size(cwd, buf_size);
		return ;
	}
}

int main(void)
{
	char	*input;

	signal(SIGQUIT, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGHUP, handle_signal);
	signal(SIGTERM, handle_signal);
	while (!exit_flag)
	{
		input = readline("Input something to echo (or type 'exit' to quit): ");
		if (input == NULL || ft_strcmp(input, "exit") == 0)
			break ;
		if (ft_strcmp(input, "pwd") == 0)
			pwd_builtin();
		add_history(input);
		printf("%s\n", input);
		free(input);
	}
	return (0);
}
