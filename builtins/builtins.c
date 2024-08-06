/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/08/06 22:26:23 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

char	*skip_set(char *str, char *set)
{
	char	*skipped;
	int		i;
	int		k;

	i = 0;
	while (str[i])
	{
		if (str[i] == set[i])
			i++;
		else
			break ;
		if (str[i] == ' ' || str[i] == '\t')
			break ;
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	skipped = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	if (!skipped)
		return (NULL);
	k = 0;
	while (str[i])
		skipped[k++] = str[i++];
	return (skipped);
}

int	echo_builtin(char *file, char **param)
{
	int		fd;
	int		i;

	fd = 1;
	i = 1;
	if (file)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (param[i] && ft_strncmp(param[i], "-n", 2) == 0)
		i++;
	while (param && param[i])
	{
		ft_putstr_fd(param[i], fd);
		i++;
		if (param[i])
			ft_putstr_fd(" ", fd);
	}
	if ((param[1] && ft_strcmp(param[1], "-n") != 0) || (!param[1]))
		ft_putstr_fd("\n", fd);
	return (EXIT_SUCCESS);
}

int	export_builtin(t_env *shell, char *new_var)
{
	int	i;
	int	found;

	i = -1;
	shell->exit_code = check_export(new_var, i);
	if (shell->exit_code != 0)
		return (shell->exit_code);
	i = 0;
	found = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], new_var,
				ft_strlen_c(shell->env[i], '=') + 1) == 0)
		{
			shell->exit_code = replace_variable(&shell->env[i], new_var);
			found = 1;
			break ;
		}
		i++;
	}
	if (ft_strcmp (new_var, "") == 0)
		return (print_list_alpha(shell->env, i));
	if (!found)
		shell->exit_code = add_variable(shell, new_var, i);
	return (shell->exit_code);
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
		if ((ft_strcmp(shell->env[i], to_unset) == 0) || (var_len == unset_len
				&& ft_strncmp(shell->env[i], to_unset, var_len) == 0))
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
	return (EXIT_SUCCESS);
}

int	env_builtin(t_env *shell, char **param)
{
	int	i;

	i = 0;
	if (shell->env == NULL)
	{
		ft_putendl_fd("Environment list not found.", 2);
		return (EXIT_FAILURE);
	}
	if (param[1])
		return (error_msg(" No such file or directory", 127));
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", (shell->env)[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
