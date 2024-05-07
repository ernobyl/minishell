/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:16:44 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/07 13:13:16 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

static int	get_builtin_num(char *input)
{
	if (ft_strncmp("exit", input, 4) == 0)
		return (EXIT);
	else if (ft_strncmp("pwd", input, 3) == 0)
		return (PWD);
	else if (ft_strncmp("cd", input, 2) == 0)
		return (CD);
	else if (ft_strncmp("echo", input, 4) == 0
			|| ft_strncmp("echo -n", input, 7) == 0)
		return (ECHO);
	else if (ft_strncmp("export", input, 6) == 0)
		return (EXPORT);
	else if (ft_strncmp("unset", input, 5) == 0)
		return (UNSET);
	else if (ft_strncmp("env", input, 3) == 0)
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

static int	match_function(int num, int ret_value, char *param, t_struct *shell)
{
	if (num == EXIT)
		ret_value = (100);
	if (num == PWD)
		ret_value = pwd_builtin();
	if (num == CD)
		ret_value = cd_builtin(param);
	if (num == ECHO)
		ret_value = echo_builtin(NULL, param);
	if (num == EXPORT)
		ret_value = export_builtin(shell, param);
	if (num == UNSET)
		ret_value = unset_builtin(shell, param);
	if (num == ENV)
		ret_value = env_builtin(shell);
	free(param);
	return (ret_value);
}

int	run_builtin(char *input, t_struct *shell)
{
	int		num;
	int		ret_value;
	char	*param;
	char	*arr[8];

	ret_value = 0;
	num = get_builtin_num(input);
	if (num == NOT_BUILTIN)
		return (101);
	init_builtin_arr(arr);
	param = skip_set(input, arr[num]);
	ret_value = match_function(num, ret_value, param, shell);
	return (ret_value);
}
