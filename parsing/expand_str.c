/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:18:09 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/08 13:40:21 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static bool	expanded_all(char *str, t_env *shell)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var = find_variable(str);
			if (!var)
				return (NULL);
			j = find_env_var(shell, var);
			if (j != -1)
				return (false);
		}
		i++;
	}
	return (true);
}

char	*find_variable(char *str)
{
	char	*var;
	int		i;
	int		start;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	start = i;
	while (str[i] && str[i] != ' ' && str[i] != '"')
		i++;
	var = ft_substr(str, start, (i - start));
	if (!var)
	{
		free(str);
		return (NULL);
	}
	i = ft_strlen(var);
	var[i] = '=';
	var[i + 1] = '\0';
	return (var);
}

int	find_env_var(t_env *shell, char *var)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	free(var);
	return (-1);
}

char	**expand_env(char **arr, t_env *shell)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		while (ft_strchr(arr[i], '$') && arr[i][0] != '\'' )
		{
			arr[i] = expand_str(arr[i], shell);
			if (!arr[i])
			{
				ft_free(arr);
				return (NULL);
			}
			if (expanded_all(arr[i], shell))
				break ;
		}
		arr[i] = trim_quote(arr[i]);
		if (!arr[i])
		{
			ft_free(arr);
			return (NULL);
		}
		i++;
	}
	return (arr);
}
