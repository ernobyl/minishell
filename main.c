/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/08/08 21:49:35 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

int	g_signal = 0;

bool	check_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i]) != ' ')
			return (false);
		i++;
	}
	return (true);
}

void	readline_loop(t_env *shell)
{
	char	*input;

	while (1)
	{
		setup_signal_handlers();
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (*input == '\0' || check_empty(input))
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

static char	*save_home(t_env *shell)
{
	char	*var;
	char	*dest;
	int		len;
	int		i;

	dest = NULL;
	i = 0;
	var = find_variable("$HOME");
	if (!var)
		return (NULL);
	len = ft_strlen(var) - 1;
	i = find_env_var(shell, var);
	if (i != -1)
	{
		dest = find_and_replace_env("$HOME", ft_strchr_next \
		(shell->env[i], '='), len);
	}
	return (dest);
}

int	main(void)
{
	t_env	shell;

	shell.env = init_env_list();
	shell.exit_code = 0;
	shell.prev_dir = NULL;
	shell.infile = "\0";
	shell.outfile = "\0";
	shell.is_empty = false;
	shell.home = save_home(&shell);
	readline_loop(&shell);
	ft_free(shell.env);
	free(shell.prev_dir);
	free(shell.home);
	return (shell.exit_code);
}
