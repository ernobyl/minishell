/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:36:22 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/07 19:34:42 by kmatjuhi         ###   ########.fr       */
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

static void	check_first(int num, char **param, t_env *shell, t_struct *token)
{
	if (num == EXIT)
		shell->exit_code = exit_builtin(param, shell, token);
	if (num == PWD)
		shell->exit_code = pwd_builtin();
	if (num == CD)
	{
		if (!param[1])
			shell->exit_code = cd_builtin(shell, NULL);
		else if (param[2])
			shell->exit_code = error_msg(" too many arguments", 1);
		else if (shell->is_empty == false)
			shell->exit_code = cd_builtin(shell, param[1]);
	}
	if (num == ECHO)
		shell->exit_code = echo_builtin(NULL, param);
}

static int	match_function(int num, char **param, t_env *shell, t_struct *token)
{
	int		i;

	check_first(num, param, shell, token);
	if (num == EXPORT)
	{
		if (param[1] == NULL)
			shell->exit_code = export_builtin(shell, "");
		else if (param[2] == NULL)
			shell->exit_code = export_builtin(shell, param[1]);
		else
			shell->exit_code = export_array(shell->exit_code, shell, param);
	}
	i = 1;
	if (num == UNSET)
	{
		while (param[i])
		{
			shell->exit_code = unset_builtin(shell, param[i]);
			i++;
		}
	}
	if (num == ENV)
		shell->exit_code = env_builtin(shell, param);
	return (shell->exit_code);
}

static int	builtin_file(t_env *shell, t_struct *token, int *fd, int num)
{
	if (shell->cmds_num == 0 && num != EXIT)
	{
		save_fds(fd);
		heredoc_open(shell, token);
		if (g_signal == 5)
		{
			shell->exit_code = 130;
			unlink(".tmp_heredoc_file");
			return (130);
		}
		if (open_files(shell, token) == 1)
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
	if (ret_value == 1 || ret_value == 130)
		return (ret_value);
	init_builtin_arr(arr);
	ret_value = match_function(num, param, shell, token);
	if (shell->cmds_num == 0 && num != EXIT)
	{
		safe_dup2(fd[0], STDIN_FILENO);
		safe_dup2(fd[1], STDOUT_FILENO);
	}
	shell->is_empty = false;
	shell->exit_code = ret_value;
	return (ret_value);
}
