/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/05/23 10:38:28 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

volatile sig_atomic_t	g_exit_flag = 0;

void	handle_signal(int sig)
{
	if (sig == SIGQUIT)
		g_exit_flag = 1;
	else if (sig == SIGINT)
		printf("\nhandle signal interrupt\n");
}

char	*skip_set(char *str, char *set)
{
	char	*skipped;
	int		i;
	int		k;

	i = 0;
	while (str[i])
	{
		if (str[i] == set[i])
			i++;
		else
			break ;
	}
	skipped = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	if (!skipped)
		return (NULL);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	k = 0;
	while (str[i])
		skipped[k++] = str[i++];
	return (skipped);
}

int	main(void)
{
	char		*input;
	t_struct	shell;
	int			ret_value;

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
			if (ft_strncmp(input, "<< ", 3) == 0)
				heredoc(skip_set(input, "<<"));
			else
				ret_value = run_builtin(input, &shell);
		}
		if (input == NULL || ret_value == EXIT_SIGNAL)
		{
			ret_value = 0;
			break ;
		}
		if (ret_value == NO_SIGNAL)
			printf("no signal\n");
		// if (parsing(input) == 0)
		// {
		// 	free(input);
		// 	return (1);
		// }
		free(input);
	}
	ft_free(shell.env);
	return (ret_value);
}
