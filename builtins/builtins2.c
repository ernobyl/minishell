/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/07/07 14:03:20 by emichels         ###   ########.fr       */
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
			return (error_msg("malloc failed", 1));
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
			return (error_msg("cd: HOME not set", 0));
		path = home;
	}
	if (chdir(path) == 0)
		return (EXIT_SUCCESS);
	else
		return (error_msg(" No such file or directory", 1));
}

int count_param(char **param)
{
	int i;

	i = 0;
	while (param[i])
		i++;
	return (i);
}
void	exit_builtin(char **param, t_env *shell)
{
	int	exit_code;
	int	param_count;

	exit_code = 0;
	param_count = count_param(param);
	if (param_count > 2)
	{
		printf(" too many arguments");
		exit_code = 1;
	}
	if (param_count == 2)
	{
		exit_code = ft_atoi(param[1]);
		if (exit_code == 0 && ft_strcmp(param[1], "0") != 0)
		{
			printf(" numeric argument required");
			exit_code = 255;
		}
	}
	ft_free(shell->env);
	ft_free(param);
	printf("exit\n");
	exit_st(exit_code);
}

int	export_array(int ret_value, t_env *shell, char **array)
{
	int	found;

	shell->k = 1;
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
		if (!found)
			ret_value = add_variable(shell, array[shell->k], shell->i);
		shell->k++;
	}
	return (ret_value);
}
