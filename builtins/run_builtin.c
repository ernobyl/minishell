/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:36:22 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/24 10:12:21 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/builtins.h"

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
		*ret_value = exit_builtin(param, shell);
	if (num == PWD)
		*ret_value = pwd_builtin();
	if (num == CD)
	{
		if (!param[1])
			*ret_value = cd_builtin(shell, NULL);
		else if (param[2])
			*ret_value = error_msg(" too many arguments", 1);
		else
			*ret_value = cd_builtin(shell, param[1]);
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
			ret_value = export_builtin(ret_value, shell, "");
		else if (param[2] == NULL)
			ret_value = export_builtin(ret_value, shell, param[1]);
		else
			ret_value = export_array(ret_value, shell, param);
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

static int	builtin_file(t_env *shell, t_struct *token, int *fd, int num)
{
	if (shell->cmds_num == 0 && num != EXIT)
	{
		save_fds(fd);
		if (open_files2(shell, token) == 1)
		{
			safe_dup2(fd[0], STDIN_FILENO);
			safe_dup2(fd[1], STDOUT_FILENO);
			shell->exit_code = 1;
			return (1);
		}
	}
	return (0);
}

int	run_builtin(char *cmd, char **param, t_env *shell, t_struct *token)
{
	int		num;
	int		ret_value;
	char	*arr[8];
	int		fd[2];

	ret_value = 0;
	num = get_builtin_num(cmd);
	if (num == NOT_BUILTIN)
		return (101);
	ret_value = builtin_file(shell, token, fd, num);
	if (ret_value == 1)
		return (ret_value);
	init_builtin_arr(arr);
	ret_value = match_function(num, ret_value, param, shell);
	if (shell->cmds_num == 0 && num != EXIT)
	{
		safe_dup2(fd[0], STDIN_FILENO);
		safe_dup2(fd[1], STDOUT_FILENO);
	}
	shell->exit_code = ret_value;
	return (ret_value);
}
