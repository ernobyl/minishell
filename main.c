/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/04/22 15:58:35 by emichels         ###   ########.fr       */
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

int main(void)
{
	char		*input;
	char		*param;
	int			fd;
	extern char	**environ;

	fd = 1;
	signal(SIGQUIT, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGHUP, handle_signal);
	signal(SIGTERM, handle_signal);
	while (!g_exit_flag)
	{
		input = readline("minishell> ");
		if (input == NULL || ft_strcmp(input, "exit") == 0)
			break ;
		if (ft_strncmp(input, "pwd", 3) == 0)
			pwd_builtin();
		if (ft_strncmp(input, "cd", 2) == 0)
		{
			param = skip_set(input, "cd");
			cd_builtin(param);
			free (param);
		}
		if (ft_strncmp(input, "echo", 4) == 0)
		{
			param = skip_set(input, "echo");
			char *file = NULL;
			//file = "testfile.txt"; // this is here for testing
			echo_builtin(fd, file, param);
			free(param);
		}
		if (ft_strncmp(input, "export", 6) == 0)
		{
			param = skip_set(input, "export");
			export_builtin(&environ, param);
			for (char **env = environ; *env != NULL; env++)
        		printf("%s\n", *env);
			free(param);
		}
		add_history(input);
		// if (parsing(input) == 0)
		// {
		// 	free(input);
		// 	return (1);
		// }
		free(input);
	}
	return (0);
}
