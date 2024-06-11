/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:18:09 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/11 14:47:30 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static char	*find_variable(char *str)
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
		return (NULL);
	i = ft_strlen(var);
	var[i] = '=';
	var[i + 1] = '\0';
	return (var);
}

static int	find_env_var(t_env *shell, char *var)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*expand_str(char *str, t_env *shell)
{
	char		*dest;
	char		*var;
	int			i;
	int			len;

	var = find_variable(str);
	if (!var)
		return (NULL);
	len = ft_strlen(var) - 1;
	i = find_env_var(shell, var);
	if (i != -1)
	{
		dest = find_and_replace(str, ft_strchr_next \
		(shell->env[i], '='), len);
	}
	else
		dest = find_and_replace(str, "\0", 0);
	free(str);
	free(var);
	return (dest);
}

char	**expand_env(char **arr, t_env *shell)
{
	int		i;

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
