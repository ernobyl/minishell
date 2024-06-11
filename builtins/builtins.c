/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/06/11 18:17:50 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	echo_builtin(char *file, char **param)
{
	int		fd;
	int		i;

	fd = 1;
	i = 1;
	if (file)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (param[i] && ft_strncmp(param[i], "-n", 2) == 0)
		i++;
	while (param && param[i])
	{
		ft_putstr_fd(param[i], fd);
		ft_putstr_fd(" ", fd);
		i++;
	}
	ft_putstr_fd("\n", fd);
	return (EXIT_SUCCESS);
}

int	export_builtin(t_env *shell, char *new_var)
{
	int	i;
	int	found;
	int	ret_value;

	i = 0;
	found = 0;
	ret_value = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], new_var,
				ft_strlen_c(shell->env[i], '=') + 1) == 0)
		{
			ret_value = replace_variable(&shell->env[i], new_var);
			found = 1;
			break ;
		}
		i++;
	}
	if (ft_strcmp (new_var, "") == 0)
		return (print_list_alpha(shell->env, i));
	else if (ft_strchr(new_var, '=') == NULL)
		return (error_msg("Invalid environment variable format."));
	if (!found)
		ret_value = add_variable(shell, new_var, i);
	return (ret_value);
}

int	unset_builtin(t_env *shell, char *to_unset)
{
	int		i;
	size_t	var_len;
	size_t	unset_len;

	i = 0;
	var_len = 0;
	unset_len = ft_strlen(to_unset);
	while (shell->env[i])
	{
		var_len = ft_strlen_c(shell->env[i], '=');
		if (var_len == unset_len
			&& ft_strncmp(shell->env[i], to_unset, var_len) == 0)
		{
			free(shell->env[i]);
			while (shell->env[i])
			{
				shell->env[i] = shell->env[i + 1];
				i++;
			}
			shell->env[i] = NULL;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

int	env_builtin(t_env *shell)
{
	int	i;

	i = 0;
	if (shell->env == NULL)
	{
		ft_putendl_fd("environment list not found", 2);
		return (EXIT_FAILURE);
	}
	while (shell->env[i])
	{
		printf("%s\n", (shell->env)[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
