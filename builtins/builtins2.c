/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/06/06 14:34:34 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

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
			return (error_msg("malloc failed"));
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
			return (error_msg("cd: HOME not set"));
		path = home;
	}
	if (chdir(path) == 0)
		return (EXIT_SUCCESS);
	else
		return (error_msg("cd failed"));
}

void	exit_builtin(char *param, t_env *shell)
{
	ft_free(shell->env);
	free(param);
	printf("exit\n");
	exit(0);
}

int	export_array(int ret_value, t_env *shell, char **array)
{
	int	found;

	shell->k = 0;
	while (array[shell->k])
	{
		found = 0;
		shell->i = 0;
		while (shell->env[shell->i])
		{
			if (ft_strncmp(shell->env[shell->i], array[shell->k],
					ft_strlen_c(shell->env[shell->i], '=') + 1) == 0)
			{
				ret_value = replace_variable(&shell->env[shell->i], array[shell->k]);
				found = 1;
				break ;
			}
			shell->i++;
		}
		if (ft_strchr(array[shell->k], '=') == NULL)
			return (error_msg("Invalid environment variable format."));
		if (!found)
			ret_value = add_variable(shell, array[shell->k], shell->i);
		shell->k++;
	}
	return (ret_value);
}