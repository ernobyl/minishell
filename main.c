/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/06/06 14:42:25 by emichels         ###   ########.fr       */
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


int	readline_loop(t_env *shell, int ret_value)
{
	char	*input;
	char	*param;
	
	while (!g_exit_flag)
	{
		input = readline("minishell> ");
		if (input == NULL) // if readline returns NULL, it means the end of input, which should exit minishell
			break ;
		if (input != NULL) // NOTE: only whitespaces (pressing enter = '\n') should not get added to history
			add_history(input);
		param = skip_set(input, input);
		ret_value = run_builtin(input, param, shell);
		// if (parsing(input, shell) == 1)
		// {
		// 	//free(input);
		// }
		//free(input);
	}
	return (ret_value);
}

int	main(void)
{
	int		ret_value;
	t_env	shell;

	shell.env = init_env_list();
	ret_value = 0;
	signal(SIGQUIT, handle_signal);
	signal(SIGINT, handle_signal);

	ret_value = readline_loop(&shell, ret_value);

	ft_free(shell.env);
	return (ret_value);
}
