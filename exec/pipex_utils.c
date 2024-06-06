/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:14:30 by emichels          #+#    #+#             */
/*   Updated: 2024/06/06 21:51:18 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	handle_error(int exitcode, const char *errormsg)
{
	perror(errormsg);
	exit(exitcode);
}

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
		if (access(path, F_OK | X_OK) == 0)
			return (freereturn(path_array, path));
		free(path);
	}
	return (freereturn(path_array, 0));
}

void	execute(char *cmd, char **args, char **envp)
{
	char	*path;
	int		i;

	path = env_path(cmd, envp);
	if (!path)
	{
		i = -1;
		while (args[++i])
			free(args[i]);
		free(args);
		handle_error(127, "command not found");
	}
	if (execve(path, args, envp) == -1)
		handle_error(127, "command not found");
}
