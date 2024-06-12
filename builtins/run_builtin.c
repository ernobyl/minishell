/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:16:44 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/12 14:05:35 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static int	get_builtin_num(char *input)
{
	// MODIFY THIS FUNCTION TO WORK WITH PARSING
	if (ft_strcmp("exit", input) == 0)
		return (EXIT);
	else if (ft_strcmp("pwd", input) == 0)
		return (PWD);
	else if (ft_strncmp("cd ", input, 3) == 0
		|| ft_strcmp("cd", input) == 0)
		return (CD);
	else if (ft_strncmp("echo ", input, 5) == 0
		|| ft_strncmp("echo -n", input, 7) == 0)
		return (ECHO);
	else if (ft_strcmp("export", input) == 0
		|| ft_strncmp("export ", input, 7)  == 0)
		return (EXPORT);
	else if (ft_strncmp("unset ", input, 6) == 0)
		return (UNSET);
	else if (ft_strcmp("env", input) == 0)
		return (ENV);
	else
		return (NOT_BUILTIN);
}

static void	init_builtin_arr(char **arr)
{
	arr[EXIT] = "exit";
	arr[PWD] = "pwd";
	arr[CD] = "cd";
	arr[ECHO] = "echo";
	arr[EXPORT] = "export";
	arr[UNSET] = "unset";
	arr[ENV] = "env";
	arr[NOT_BUILTIN] = NULL;
}

static int	match_function(int num, int ret_value, char **param, t_env *shell)
{
	//char	**array;
	int		i;

	i = 0;
	if (num == EXIT)
		exit_builtin(param, shell);
	if (num == PWD)
		ret_value = pwd_builtin();
	if (num == CD)
		ret_value = cd_builtin(param[1]);
	if (num == ECHO)
		ret_value = echo_builtin(NULL, param);
	if (num == EXPORT)
	{
		//array = ft_split(param, ' ');
		if (param[0] == NULL || param[1] == NULL)
			ret_value = export_builtin(ret_value, shell, param[0]);
		//else
		ret_value = export_array(ret_value, shell, param);
		//ft_free(array);
	}
	while (param[i])
	{
		if (num == UNSET)
			ret_value = unset_builtin(shell, param[i]);
		i++;
	}
	if (num == ENV)
		ret_value = env_builtin(shell);
	return (ret_value);
}

int	run_builtin(char *cmd, char **param, t_env *shell)
{
	int		num;
	int		ret_value;
	char	*arr[8];

	ret_value = 0;
	num = get_builtin_num(cmd);
	if (num == NOT_BUILTIN)
		return (101);
	init_builtin_arr(arr);
	ret_value = match_function(num, ret_value, param, shell);
	return (ret_value);
}
