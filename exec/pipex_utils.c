/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:14:30 by emichels          #+#    #+#             */
/*   Updated: 2024/07/24 21:26:23 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static char	*freereturn(char **tofree, char *toreturn)
{
	int	i;

	i = -1;
	while (tofree[++i])
		free(tofree[i]);
	free(tofree);
	return (toreturn);
}

static char	*env_path(char *cmd, char **envp)
{
	char	**path_array;
	char	*path;
	int		i;
	char	*subdir_path;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path_array = ft_split(envp[i] + 5, ':');
	i = -1;
	while (path_array && path_array[++i])
	{
		subdir_path = ft_strjoin(path_array[i], "/");
		path = ft_strjoin(subdir_path, cmd);
		free(subdir_path);
		if (access(path, F_OK) == 0)
			return (freereturn(path_array, path));
		free(path);
	}
	return (freereturn(path_array, 0));
}

static void	is_dir(t_env *shell, char *str)
{
	int		fd3;

	fd3 = open(str, O_DIRECTORY);
	if (fd3 != -1)
	{
		close(fd3);
		handle_error_exec(126, shell, str, ": is a directory\n");
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
