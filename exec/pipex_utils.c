/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:14:30 by emichels          #+#    #+#             */
/*   Updated: 2024/08/01 10:57:15 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static void	is_dir(t_env *shell, char *str)
{
	int		fd3;

	fd3 = open(str, O_DIRECTORY);
	if (fd3 != -1)
	{
		close(fd3);
		handle_error_exec(126, shell, str, ": Is a directory\n");
	}
}

static void	is_direct_xcute(t_env *shell, char *cmd, char **args, char **envp)
{
	if (ft_strrchr(cmd, '/'))
	{
		is_dir(shell, args[0]);
		if (access(args[0], F_OK) != 0)
			handle_error_exec(127, shell, cmd, ": No such file or directory\n");
		execve(args[0], args, envp);
		handle_error_exec(126, shell, cmd, ": Permission denied\n");
	}
}

void	execute(t_env *shell, char *cmd, char **args, char **envp)
{
	char	*path;
	int		len;

	len = ft_strlen(cmd);
	is_direct_xcute(shell, cmd, args, envp);
	while (cmd[len] && cmd[len] != '/')
		len--;
	path = env_path(cmd, envp);
	if (!path || (access(path, X_OK == -1)))
	{
		if (!path)
			handle_error_exec(127, shell, cmd, "command not found");
		else
		{
			free(path);
			handle_error_exec(126, shell, cmd, ": Permission denied\n");
		}
	}
	if (ft_strcmp(cmd, "minishell") == 0 || ft_strcmp(cmd + len, "minishell"))
		export_shlvl(envp);
	if (execve(path, args, envp) == -1)
		handle_error_exec(127, shell, cmd, "command not found");
}
