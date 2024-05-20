/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:18:09 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/20 13:22:38 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

static char	*expand_str(char *str)
{
	char		*var;
	char		*dest;
	int			i;
	extern char	**environ;

	i = 0;
	var = find_variable(str);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var, ft_strlen(var)) == 0)
		{
			dest = find_and_replace(str, ft_strchr_next(environ[i], '='), ft_strlen(var) - 1);
			return (dest);
		}
		i++;
	}
	dest = find_and_replace(str, "\0", 0);
	return (dest);
}

char	**expand_env(char **arr)
{
	int		i;
	char	*str;

	i = 0;
	while (arr[i])
	{
		if (ft_strchr(arr[i], '$') && arr[i][0] != '\'' )
		{
			if (validate_expand(arr[i]))
				arr[i] = expand_str(arr[i]);
		}
		arr[i] = trim_quote(arr[i]);
		i++;
	}
	return (arr);
}
