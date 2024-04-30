/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/04/29 15:32:18 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (EXIT_FAILURE);
}

int	double_buf_size(char **str, size_t *buf_size)
{
	if (errno == ERANGE)
	{
		*buf_size *= 2;
		free(*str);
		*str = malloc(*buf_size);
		if (*str == NULL)
			return (error_msg("malloc failed"));
		return (EXIT_SUCCESS);
	}
	else
	{
		free(*str);
		return (error_msg("pwd: getcwd failed"));
	}
}

int	replace_variable(char **env_var, char *new_var)
{
	free(*env_var);
	*env_var = ft_strdup(new_var);
	if (*env_var == NULL)
		return (error_msg("strdup failed"));
	return (EXIT_SUCCESS);
}

int	add_variable(char ***environ, char *new_var, int size)
{
	char	**add_env;

	add_env = malloc((size + 2) * sizeof(char *));
	if (add_env == NULL)
		return (error_msg("malloc failed"));
	ft_memcpy(add_env, *environ, size * sizeof(char *));
	add_env[size] = ft_strdup(new_var);
	if (add_env[size] == NULL)
	{
		free(add_env);
		return (error_msg("strdup failed"));
	}
	add_env[size + 1] = NULL;
	free (*environ);
	*environ = add_env;
	return (EXIT_SUCCESS);
}
