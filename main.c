/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/07/24 11:27:33 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtins.h"
#include "includes/parsing.h"

int	readline_loop(t_env *shell, int ret_value)
{
	char	*input;

	setup_signal_handlers();
	while (1)
	{
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
			ret_value = 1;
	}
	reset_signal_handlers();
	return (ret_value);
}

int	main(void)
{
	int		ret_value;
	t_env	shell;

	shell.env = init_env_list();
	shell.exit_code = 0;
	shell.prev_dir = NULL;
	ret_value = 0;
	ret_value = readline_loop(&shell, ret_value);
	ft_free(shell.env);
	free(shell.prev_dir);
	return (ret_value);
}
