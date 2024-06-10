/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/06/10 21:26:04 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtins.h"
#include "includes/parsing.h"

volatile	sig_atomic_t	g_exit_flag = 0;

void	handle_signal(int sig)
{
	if (sig == SIGQUIT)
		g_exit_flag = 1;
	else if (sig == SIGINT)
		printf("\nhandle signal interrupt\n");
}

int	main(void)
{
	t_env	shell;
	char	*input;
	int		ret_value;

	shell.env = init_env_list();
	ret_value = 0;
	signal(SIGQUIT, handle_signal);
	signal(SIGINT, handle_signal);
	while (!g_exit_flag)
	{
		input = readline("minishell> ");
		if (input != NULL)
		{
			add_history(input);
			if (parsing(input, &shell) == 0)
			{
				ret_value = 1;
				break ;
			}
			// if (ft_strncmp(input, "<< ", 3) == 0)
			// 	heredoc(skip_set(input, "<<"));
		}
		if (input == NULL || ret_value == EXIT_SIGNAL)
		{
			ret_value = 0;
			break ;
		}
		if (ret_value == NO_SIGNAL)
			printf("no signal\n");
	}
	ft_free(shell.env);
	return (ret_value);
}
