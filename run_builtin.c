/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:16:44 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/29 15:19:53 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_builtin_arr(char **builtin_arr)
{
	builtin_arr[0] = "exit";
	builtin_arr[1] = "pwd";
	builtin_arr[2] = "cd";
	builtin_arr[3] = "echo";
	builtin_arr[4] = "export";
	builtin_arr[5] = "unset";
	builtin_arr[6] = "env";
}

int	run_builtin(char *input)
{
	int			ret_value;
	char		*param;
	extern char	**environ;
	char		*builtin_arr[7];

	ret_value = 0;
	init_builtin_arr(builtin_arr);
	if (input == NULL || ft_strcmp(input, "exit") == 0)
		return (100);
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
	return (ret_value);
}
