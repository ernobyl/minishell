/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/05/07 09:53:10 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

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
	free((*env_var));
	*env_var = ft_strdup(new_var);
	if ((*env_var) == NULL)
		return (error_msg("strdup failed"));
	return (EXIT_SUCCESS);
}

int	add_variable(t_struct *shell, char *new_var, int size)
{
	char	**add_env;
	int		i;

	add_env = malloc((size + 2) * sizeof(char *));
	if (add_env == NULL)
		return (error_msg("malloc failed"));
	i = 0;
	while (i < size)
	{
		add_env[i] = ft_strdup(shell->env[i]);
		i++;
	}
	add_env[i] = ft_strdup(new_var);
	add_env[i + 1] = NULL;
	shell->env = add_env;
	return (EXIT_SUCCESS);
}
