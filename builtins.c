/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/04/29 15:32:18 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		ret_value;

	i = 0;
	found = 0;
	ret_value = 0;
	if (new_var == NULL || ft_strchr(new_var, '=') == NULL)
		return (error_msg("Invalid environment variable format."));
	while ((*environ)[i])
	{
		if (strncmp((*environ)[i], new_var, ft_strlen_c((*environ)[i], '=') + 1) == 0)
		{
			ret_value = replace_variable(&(*environ)[i], new_var);
			found = 1;
			break ;
		}
		i++;
	}
	if (!found)
		ret_value = add_variable(environ, new_var, i);
	return (ret_value);
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
