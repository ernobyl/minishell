/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/04/22 15:42:02 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	double_buf_size(char *str, size_t buf_size)
{
	if (errno == ERANGE)
	{
		buf_size *= 2;
		free(str);
	}
	else
	{
		perror("pwd: getcwd failed");
		free(str);
		return ;
	}
}

void	pwd_builtin(void)
{
	size_t	buf_size;
	char	*cwd;

	buf_size = 256;
	cwd = NULL;
	cwd = malloc(buf_size);
	if (cwd == NULL)
	{
		perror("malloc failed");
		return ;
	}
	if (getcwd(cwd, buf_size) != NULL)
	{
		printf("%s\n", cwd);
		free(cwd);
		return ;
	}
	else
	{
		double_buf_size(cwd, buf_size);
		return ;
	}
}

void    cd_builtin(const char *path)
{
    const char  *home;
    
    if (path == NULL || ft_strcmp(path, "") == 0)
    {
        home = getenv("HOME");
        if (home == NULL)
        {
            printf("cd: HOME not set");
            return ;
        }
        path = home;
    }
    if (chdir(path) == 0)
        return ;
    else
        perror("cd");
}

void    echo_builtin(char *file, char *input)
{
	char	*to_echo;
	int		fd;

	fd = 1;
	to_echo = NULL;
	if (file)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (strncmp(input, "-n", 2) == 0)
	{
		to_echo = skip_set(input, "-n");
		ft_putstr_fd(to_echo, fd);
		free(to_echo);
	}
	else
		ft_putendl_fd(input, fd);
    return ;
}

void    export_builtin(char ***environ, char *new_var)
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
		return ;
	}
	while ((*environ)[i])
	{
		if (ft_strcmp((*environ)[i], new_var) == 0)
		{
			free((*environ)[i]);
			(*environ)[i] = ft_strdup(new_var);
			if ((*environ)[i] == NULL)
			{
				ft_putendl_fd("strdup failed", 2);
				return ;
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
			return ;
		}
		ft_memcpy(add_env, *environ, i * sizeof(char *));
		add_env[i] = ft_strdup(new_var);
		if (add_env[i] == NULL)
		{
			ft_putendl_fd("strdup failed", 2);
			free(add_env);
			return ;
		}
		add_env[i + 1] = NULL;
		free (*environ);
		*environ = add_env;
	}
}