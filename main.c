/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/07/06 14:18:23 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtins.h"
#include "includes/parsing.h"

void	handle_signal(int sig)
{
	if (sig == SIGQUIT)
		g_signal_flag = 1;
	else if (sig == SIGINT)
	{
		g_signal_flag = 2;
		write(1, "\n", 1);
	}
}


int	readline_loop(t_env *shell, int ret_value)
{
	char	*input;

	while (g_signal_flag != 1)
	{
		signal(SIGQUIT, handle_signal);
		signal(SIGINT, handle_signal);
		g_signal_flag = 0;
		if (g_signal_flag == 2)
			continue ;
		input = readline("minishell> ");
		if (input == NULL) // if readline returns NULL, it means the end of input, which should exit minishell
			break ;
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		else if (input != NULL) // NOTE: only whitespaces (pressing enter = '\n') should not get added to history
			add_history(input);
		if (parsing(input, shell) == 0)
			ret_value = 1;
	}
	return (ret_value);
}

int	main(void)
{
	int		ret_value;
	t_env	shell;

	shell.env = init_env_list();
	ret_value = 0;
	ret_value = readline_loop(&shell, ret_value);
	ft_free(shell.env);
	// close(STDIN_FILENO);
	// close(STDOUT_FILENO);
	return (ret_value);
}
