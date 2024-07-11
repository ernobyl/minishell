/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/07/11 17:34:43 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	check_export(char *new_var, int i)
{
	int	k;

	while (new_var[++i])
	{
		if (new_var[0] == '=')
			return (error_msg(" not a valid identifier", 1));
		else if (new_var[i] == '=')
			break ;
		else if (!ft_isalnum(new_var[i]))
			return (error_msg(" not a valid identifier", 1));
		k = 0;
		if (ft_isdigit(new_var[i]))
		{
			while (new_var[k])
			{
				if (ft_isalpha(new_var[k]))
					break ;
				if (!ft_isalpha(new_var[k]))
					k++;
				if (new_var[k] == '\0' || new_var[k] == '=')
					return (error_msg(" not a valid identifier", 1));
			}
		}
	}
	return (0);
}

char	*current_dir(void)
{
	size_t	buf_size;
	char	*cwd;

	buf_size = 1024;
	cwd = NULL;
	cwd = malloc(buf_size);
	if (cwd == NULL)
	{
		ft_putendl_fd("malloc failed", 1);
		return (NULL);
	}
	if (getcwd(cwd, buf_size) != NULL)
		return (cwd);
	return (NULL);
}

void	env_replace_var(t_env *shell, char *replace)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], replace,
				ft_strlen_c(shell->env[i], '=') + 1) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(replace);
			return ;
		}
		i++;
	}
}

char	*custom_getenv(t_env *shell, char *var)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var,
				ft_strlen_c(shell->env[i], '=')) == 0)
		{
			return (shell->env[i] + ft_strlen_c(shell->env[i], '=') + 1);
		}
		i++;
	}
	return (NULL);
}

int	handle_oldpwd(t_env *shell, char *prev_dir)
{
	char	*old_pwd;

	prev_dir = custom_getenv(shell, "OLDPWD");
	if (!prev_dir)
		return (1);
	old_pwd = ft_strjoin("OLDPWD=", current_dir());
	if (chdir(prev_dir) == 0)
	{
		printf("%s\n", prev_dir);
		env_replace_var(shell, old_pwd);
		free(old_pwd);
	}
	return (0);
}
