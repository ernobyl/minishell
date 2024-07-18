/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/07/18 14:58:52 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtins.h"
#include "includes/parsing.h"

// void check_for_leaks() {
//     pid_t pid = getpid();
//     char command[256];
//     snprintf(command, sizeof(command), "leaks %d", pid);
//     system(command);
// }

//int	g_signal_flag = 0;

void handle_signal(int sig)
{
    if (sig == SIGQUIT)
	{
		printf("ASS");
        // g_signal_flag = 1;
		// g_signal_flag = 0;
	}
    else if (sig == SIGINT)
	{
        //g_signal_flag = 2;
        rl_replace_line("", 0);
        rl_on_new_line();
        printf("\n");
        rl_redisplay();
		//g_signal_flag = 0;
    }
}

void setup_signal_handlers(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

int	readline_loop(t_env *shell, int ret_value)
{
	char	*input;
	
	setup_signal_handlers();
	while (1)
	{
		input = readline("minishell> ");
		// if (g_signal_flag == 2)
		// {
		// 	free(input);
		// 	continue ;
		// }
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
		// check_for_leaks();
	}
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
