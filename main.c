/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/04/29 15:19:58 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_flag = 0;

void	handle_signal(int sig)
{
	if (sig == SIGQUIT || sig == SIGHUP || sig == SIGTERM)
		g_exit_flag = 1;
	else if (sig == SIGINT)
		write(1, "\nhandle signal interrupt\n", 25);
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
	extern char	**environ;
	char		*input;
	int			ret_value;

	ret_value = 0;
	signal(SIGQUIT, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGHUP, handle_signal);
	signal(SIGTERM, handle_signal);
	while (!g_exit_flag)
	{
		input = readline("minishell> ");
		add_history(input);
		ret_value = built_ins(input, environ);
		if (ret_value == 100)
			g_exit_flag = 1;
		// if (parsing(input) == 0)
		// {
		// 	free(input);
		// 	return (1);
		// }
		free(input);
	}
	return (ret_value);
}
