/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/07/09 19:51:59 by kmatjuhi         ###   ########.fr       */
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

int	count_param(char **param)
{
	int	i;

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
		ft_putendl_fd(" too many arguments", 2);
		exit_code = 1;
	}
	if (param_count == 2)
	{
		exit_code = ft_atoi(param[1]);
		if (exit_code == 0 && ft_strcmp(param[1], "0") != 0)
		{
			ft_putendl_fd(" numeric argument required", 2);
			exit_code = 255;
		}
	}
	ft_free(shell->env);
	ft_free(param);
	printf("exit\n");
	exit(exit_code);
}

int	export_array(int r_val, t_env *shell, char **ar)
{
	shell->k = 1;
	while (ar[shell->k])
	{
		shell->i = -1;
		r_val = check_export(ar[shell->k], shell->i);
		if (r_val != 0)
			return (r_val);
		shell->found = 0;
		shell->i = 0;
		while (shell->env[shell->i])
		{
			if (ft_strncmp(shell->env[shell->i], ar[shell->k],
					ft_strlen_c(shell->env[shell->i], '=') + 1) == 0)
			{
				r_val = replace_variable(&shell->env[shell->i], ar[shell->k]);
				shell->found = 1;
				break ;
			}
			shell->i++;
		}
		if (!shell->found)
			r_val = add_variable(shell, ar[shell->k], shell->i);
		shell->k++;
	}
	return (r_val);
}
