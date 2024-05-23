/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:18:09 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/23 14:24:21 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	validate_expand(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		return (true);
	while (str[i] != '$')
		i++;
	if (str[i - 1] != ' ' && str[i - 1] != '"')
		return (false);
	return (true);
}

static char	*find_variable(char *str)
{
	char	*var;
	int		start;
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	start = i;
	while (str[i] && str[i] != ' ' && str[i] != '"')
		i++;
	var = ft_substr(str, start, (i - start));
	i = ft_strlen(var);
	var[i] = '=';
	var[i + 1] = '\0';
	return (var);
}

static char	*expand_str(char *str, t_env *shell)
{
	char		*var;
	char		*dest;
	int			i;

	// find all $signs and change it, can be several in 1 string;

	i = 0;
	var = find_variable(str);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var)) == 0)
		{
			dest = find_and_replace(str, ft_strchr_next(shell->env[i], '='), ft_strlen(var) - 1);
			return (dest);
		}
		i++;
	}
	dest = find_and_replace(str, "\0", 0);
	return (dest);
}

char	**expand_env(char **arr, t_env *shell)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (ft_strchr(arr[i], '$') && arr[i][0] != '\'' )
		{
			if (validate_expand(arr[i]))
				arr[i] = expand_str(arr[i], shell);
		}
		arr[i] = trim_quote(arr[i]);
		i++;
	}
	return (arr);
}
