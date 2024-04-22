/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/04/22 11:18:43 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	exit_flag = 0;

void	handle_signal(int sig)
{
	if (sig == SIGQUIT || sig == SIGHUP || sig == SIGTERM)
		exit_flag = 1;
	else if (sig == SIGINT)
		write(1, "\nhandle signal interrupt\n", 25);
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
		add_history(input);
		printf("%s\n", input);
		free(input);
	}
	return (0);
}
