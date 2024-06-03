/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/06/03 13:09:48 by kmatjuhi         ###   ########.fr       */
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
	if (input != NULL)
	{
		add_history(input);
		if (parsing(input, shell) == 0)
		{
			free(input);
			return (1);
		}
	}
	if (input == NULL)
		return (EXIT);
	return (0);
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
	while (!g_exit_flag)
	{
		input = readline("minishell> ");
		ret_value = readline_loop(input, &shell, ret_value);
		if (ret_value == 1)
			break ;
	}
	ft_free(shell.env);
	return (ret_value);
}
