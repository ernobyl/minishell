/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:56:43 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/01 11:04:50 by kmatjuhi         ###   ########.fr       */
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

static int	find_env(char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		i++;
		j++;
	}
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (i == j)
		return (-1);
	return (i);
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
	i = find_env(envp);
	if (i == -1)
		return (NULL);
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
