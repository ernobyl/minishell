/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/06/03 13:53:42 by emichels         ###   ########.fr       */
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

int	readline_loop(char *input, t_env *shell, int ret_value)
{
	while (!g_exit_flag)
	{
		input = readline("minishell> ");
		printf("1\n");
		if (input != NULL)
		{
			add_history(input);
			if (parsing(input, shell) == 1)
			{
				free(input);
			}
		}
		printf("2\n");
	}
	return (EXIT_MAIN);
}

int	main(void)
{
	char	*input;
	int		ret_value;
	t_env	shell;

	shell.env = init_env_list();
	ret_value = 0;
	signal(SIGQUIT, handle_signal);
	signal(SIGINT, handle_signal);

	ret_value = readline_loop(input, &shell, ret_value);

	ft_free(shell.env);
	return (ret_value);
}
