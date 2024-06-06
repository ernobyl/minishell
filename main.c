/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/06/06 13:23:59 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtins.h"
# include "includes/parsing.h"

volatile sig_atomic_t	g_exit_flag = 0;

void	handle_signal(int sig)
{
	if (sig == SIGQUIT)
		g_exit_flag = 1;
	else if (sig == SIGINT)
		printf("\nhandle signal interrupt\n");
}

int	main(void)
{
	char	*input;
	t_env	shell;
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
				free(input);
				return (1);
			}
			// if (ft_strncmp(input, "<< ", 3) == 0)
			// 	heredoc(skip_set(input, "<<"));
			// else
			// 	ret_value = run_builtin(input, &shell);
		}
		if (input == NULL || ret_value == EXIT_SIGNAL)
		{
			ret_value = 0;
			break ;
		}
		if (ret_value == NO_SIGNAL)
			printf("no signal\n");
		// free(input);
	}
	ft_free(shell.env);
	return (ret_value);
}
