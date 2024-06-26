/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/27 10:38:34 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/builtins.h"

static int	get_builtin_num(char *input)
{
	if (ft_strcmp("exit", input) == 0)
		return (EXIT);
	else if (ft_strcmp("pwd", input) == 0)
		return (PWD);
	else if (ft_strncmp("cd ", input, 3) == 0
		|| ft_strcmp("cd", input) == 0)
		return (CD);
	else if (ft_strcmp("echo", input) == 0
		|| ft_strncmp("echo -n", input, 7) == 0)
		return (ECHO);
	else if (ft_strcmp("export", input) == 0
		|| ft_strncmp("export ", input, 7)  == 0)
		return (EXPORT);
	else if (ft_strcmp("unset", input) == 0)
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

static void	check_first(int num, int *ret_value, char **param, t_env *shell)
{
	if (num == EXIT)
		exit_builtin(param, shell);
	if (num == PWD)
		*ret_value = pwd_builtin();
	if (num == CD)
	{
		if (param[2])
		{
			ft_putendl_fd(" too many arguments\n", 2);
			*ret_value = 1;
		}
		else
			*ret_value = cd_builtin(param[1]);
	}
	if (num == ECHO)
		*ret_value = echo_builtin(NULL, param);
}

static int	match_function(int num, int ret_value, char **param, t_env *shell)
{
	int		i;

	check_first(num, &ret_value, param, shell);
	if (num == EXPORT)
	{
		if (param[1] == NULL)
		{
			ret_value = export_builtin(ret_value, shell, "");
			// printf("export 1 ret %d", ret_value);
		}
		else if (param[2] == NULL)
		{
			ret_value = export_builtin(ret_value, shell, param[1]);
			// printf("export 2 ret %d", ret_value);
		}
		else
		{
			ret_value = export_array(ret_value, shell, param);
			// printf("export 3 ret %d", ret_value);
		}
	}
	i = 1;
	if (num == UNSET)
	{
		while (param[i])
		{
			ret_value = unset_builtin(shell, param[i]);
			i++;
		}
	}
	if (num == ENV)
		ret_value = env_builtin(shell);
	return (ret_value);
}

int	run_builtin(char *cmd, char **param, t_env *shell, t_struct *token)
{
	int		num;
	int		ret_value;
	char	*arr[8];

	ret_value = 0;
	num = get_builtin_num(cmd);
	if (num == EXIT)
		free(token);
	if (num == NOT_BUILTIN)
		return (101);
	init_builtin_arr(arr);
	ret_value = match_function(num, ret_value, param, shell);
	g_exit_status = ret_value;
	// printf("%d\n", g_exit_status);
	return (ret_value);
}
