/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:16:44 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/29 13:23:56 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_ins(char *input, sig_atomic_t flag)
{
	int			ret_value;
	char		*param;
	extern char	**environ;

	ret_value = 0;
	while (!flag)
	{
		input = readline("minishell> ");
		if (input == NULL || ft_strcmp(input, "exit") == 0)
			break ;
		if (ft_strncmp(input, "pwd", 3) == 0)
			ret_value = pwd_builtin();
		if (ft_strncmp(input, "cd", 2) == 0)
		{
			param = skip_set(input, "cd");
			ret_value = cd_builtin(param);
			free (param);
		}
		if (ft_strncmp(input, "echo", 4) == 0)
		{
			param = skip_set(input, "echo");
			char *file = NULL;
			//file = "testfile.txt"; // this is here for testing
			ret_value = echo_builtin(file, param);
			free(param);
		}
		if (ft_strncmp(input, "export", 6) == 0)
		{
			param = skip_set(input, "export");
			ret_value = export_builtin(&environ, param);
			free(param);
		}
		if (ft_strncmp(input, "unset", 5) == 0)
		{
			param = skip_set(input, "unset");
			ret_value = unset_builtin(&environ, param);
			free(param);
		}
		if (ft_strncmp(input, "env", 3) == 0)
		{
			ret_value = env_builtin(environ);
		}
	}
	return (ret_value);
}
