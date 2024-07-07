/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:13:02 by emichels          #+#    #+#             */
/*   Updated: 2024/07/07 21:42:09 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static char	**free_return(char **env)
{
	ft_free(env);
	return (NULL);
}

static void	replace_shlvl(char **env_var, char *new_var)
{
	free((*env_var));
	*env_var = ft_strdup(new_var);
}

char	**init_env_list(void)
{
	char	**env;
	int		len;
	int		i;
	int		var_len;

	len = 0;
	while (environ[len])
		len++;
	env = (char **)malloc((len + 1) * sizeof(char *));
	if (env == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		var_len = ft_strlen(environ[i]) + 1;
		env[i] = malloc(var_len);
		if (env[i] == NULL)
			return (free_return(env));
		ft_memcpy(env[i], environ[i], var_len);
		i++;
	}
	env[len] = NULL;
	return (env);
}

char	*create_new_shlvl(const char *prefix, int new_level)
{
	char	*new_var;
	char	*level_str;
	size_t	len;

	level_str = ft_itoa(new_level);
	if (!level_str)
		return (NULL);
	len = ft_strlen(prefix) + ft_strlen(level_str) + 1;
	new_var = (char *)malloc(len);
	if (!new_var)
	{
		free(level_str);
		return (NULL);
	}
	ft_strlcpy(new_var, prefix, ft_strlen(prefix) + 1);
	ft_strlcat(new_var, level_str, ft_strlen(new_var) + 2);
	free(level_str);
	return (new_var);
}

void	export_shlvl(char **envp)
{
	int		i;
	int		num;
	char	*new_shlvl;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			num = ft_atoi(envp[i] + 6) + 1;
		i++;
	}
	new_shlvl = create_new_shlvl("SHLVL=", num);
	i = 0;
	if (!new_shlvl)
		return ;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			replace_shlvl(&envp[i], new_shlvl);
			free(new_shlvl);
			return ;
		}
		i++;
	}
}
