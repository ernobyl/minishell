/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/07/31 12:05:57 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

int	g_signal = 0;

void	readline_loop(t_env *shell)
{
	char	*input;

	while (1)
	{
		setup_signal_handlers();
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		else if (input != NULL)
			add_history(input);
		if (parsing(input, shell) == 0)
			shell->exit_code = 1;
	}
	reset_signal_handlers();
}

int	main(int argc, char **argv)
{
	t_env	shell;

	(void)argv;
	if (argc != 1)
	{
		error_msg("minishell does not accept additional arguments", 1);
		return (1);
	}
	shell.env = init_env_list();
	shell.exit_code = 0;
	shell.prev_dir = NULL;
	readline_loop(&shell);
	ft_free(shell.env);
	free(shell.prev_dir);
	return (shell.exit_code);
}
