/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:14:30 by emichels          #+#    #+#             */
/*   Updated: 2024/07/07 21:48:05 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*freereturn(char **tofree, char *toreturn)
{
	int	i;

	i = -1;
	while (tofree[++i])
		free(tofree[i]);
	free(tofree);
	return (toreturn);
}

char	*env_path(char *cmd, char **envp)
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

static void	is_dir(char **args, char *str)
{
	int		fd3;

	fd3 = open(str, O_DIRECTORY);
	if (fd3 != -1)
	{
		close(fd3);
		handle_error_exec(126, str, ": is a directory\n");
	}
}

void	execute(char *cmd, char **args, char **envp, int *fd)
{
	char	*path;
	int		i;
	int		len;
	
	len = ft_strlen(cmd);
	if (ft_strrchr(cmd, '/'))
	{
		is_dir(args, args[0]);
		if (access(args[0], F_OK) != 0)
			handle_error_exec(127, cmd, ": No such file or directory\n");
		execve(args[0], args, envp);
		handle_error_exec(126, cmd, ": Permission denied\n");
	}
	while (cmd[len] && cmd[len] != '/')
		len--;
	path = env_path(cmd, envp);
	if (!path)
	{
		i = -1;
		while (args[++i])
			free(args[i]);
		free(args);
		handle_error_exec(127, cmd, "command not found");
	}
	if (access(path, X_OK == -1))
	{
		i = -1;
		while (args[++i])
			free(args[i]);
		free(args);
		free(path);
		handle_error_exec(126, cmd, ": Permission denied\n");
	}
	if (ft_strcmp(cmd, "minishell") == 0 || ft_strcmp(cmd + len, "minishell"))
		export_shlvl(envp);
	if (execve(path, args, envp) == -1)
		handle_error_exec(127, cmd, "command not found");
}
