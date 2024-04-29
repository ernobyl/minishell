/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/04/29 12:06:38 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	double_buf_size(char **str, size_t *buf_size)
{
	if (errno == ERANGE)
	{
		*buf_size *= 2;
		free(*str);
		*str = malloc(*buf_size);
		if (*str == NULL)
		{
			perror("malloc failed");
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("pwd: getcwd failed");
		free(*str);
		return (EXIT_FAILURE);
	}
}

int	pwd_builtin(void)
{
	size_t	buf_size;
	char	*cwd;
	int		result;

	buf_size = 256;
	cwd = NULL;
	while (1)
	{
		cwd = malloc(buf_size);
		if (cwd == NULL)
		{
			perror("malloc failed");
			return (EXIT_FAILURE);
		}
		if (getcwd(cwd, buf_size) != NULL)
		{
			printf("%s\n", cwd);
			free(cwd);
			return (EXIT_SUCCESS);
		}
		else
		{
			result = double_buf_size(&cwd, &buf_size);
			if (result == EXIT_FAILURE)
				return (result);
		}
	}
}

int	cd_builtin(const char *path)
{
	const char	*home;

	if (path == NULL || ft_strcmp(path, "") == 0)
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			printf("cd: HOME not set");
			return (EXIT_FAILURE);
		}
		path = home;
	}
	if (chdir(path) == 0)
		return (EXIT_SUCCESS);
	else
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
}

int	echo_builtin(char *file, char *input)
{
	char	*to_echo;
	int		fd;

	fd = 1;
	to_echo = NULL;
	if (file)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (ft_strncmp(input, "-n", 2) == 0)
	{
		to_echo = skip_set(input, "-n");
		ft_putstr_fd(to_echo, fd);
		free(to_echo);
	}
	else
		ft_putendl_fd(input, fd);
	return (EXIT_SUCCESS);
}

int	export_builtin(char ***environ, char *new_var)
{
	int		i;
	int		found;
	char	**add_env;

	i = 0;
	found = 0;
	add_env = NULL;
	if (new_var == NULL || ft_strchr(new_var, '=') == NULL)
	{
		ft_putendl_fd("Invalid environment variable format.", 2);
		return (EXIT_FAILURE);
	}
	while ((*environ)[i])
	{
		if (ft_strncmp((*environ)[i], new_var, ft_strlen_c((*environ)[i], '=') + 1) == 0)
		{
			free((*environ)[i]);
			(*environ)[i] = ft_strdup(new_var);
			if ((*environ)[i] == NULL)
			{
				ft_putendl_fd("strdup failed", 2);
				return (EXIT_FAILURE);
			}
			found = 1;
			break ;
		}
		i++;
	}
	if (!found)
	{
		add_env = malloc((i + 2) * sizeof(char *));
		if (add_env == NULL)
		{
			ft_putendl_fd("malloc failed", 2);
			return (EXIT_FAILURE);
		}
		ft_memcpy(add_env, *environ, i * sizeof(char *));
		add_env[i] = ft_strdup(new_var);
		if (add_env[i] == NULL)
		{
			ft_putendl_fd("strdup failed", 2);
			free(add_env);
			return (EXIT_FAILURE);
		}
		add_env[i + 1] = NULL;
		free (*environ);
		*environ = add_env;
	}
	return (EXIT_SUCCESS);
}

int	unset_builtin(char ***environ, char *to_unset)
{
	int		i;
	size_t	var_len;
	size_t	unset_len;

	i = 0;
	var_len = 0;
	unset_len = ft_strlen(to_unset);
	while ((*environ)[i])
	{
		var_len = ft_strlen_c((*environ)[i], '=');
		if (var_len == unset_len && ft_strncmp((*environ)[i], to_unset, var_len) == 0)
		{
			free((*environ)[i]);
			while ((*environ)[i])
			{
				(*environ)[i] = (*environ)[i + 1];
				i++;
			}
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

int	env_builtin(char **environ)
{
	int	i;

	i = 0;
	if (environ == NULL)
	{
		ft_putendl_fd("environment list not found", 2);
		return (EXIT_FAILURE);
	}
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
