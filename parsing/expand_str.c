/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:18:09 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/07 22:26:12 by kmatjuhi         ###   ########.fr       */
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

bool	check_match_exitcode(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$')
		i++;
	if (str[++i] == '?')
		return (true);
	return (false);
}
char	*find_and_replace_exitcode(char *str)
{
	int		len;
	char	*exit_code;
	char	*dest;
	int		i;
	int		j;

	j = 0;
	i = 0;
	exit_code = ft_itoa(g_exit_status);
	len = ft_strlen(str) - 2 + ft_strlen(exit_code);
	dest = malloc(len + 1);

	while (str[i] != '$')
		dest[j++] = str[i++];
	if (str[++i] == '?')
	{
		i++;
		while (*exit_code)
			dest[j++] = *exit_code++;
	}
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	return (dest);
}
char	*check_single_dollar(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i + 1] == ' ' || str[i + 1] == '\0' || str[i + 1] == '"')
		return (str);
	free(str);
	new = malloc(sizeof(char) * 1);
	new[0] = '\0';
	return (new);
}

static char	*expand_str(char *str, t_env *shell)
{
	char		*dest;
	char		*var;
	int			i;
	int			len;

	if (check_match_exitcode(str))
		dest = find_and_replace_exitcode(str);
	else
	{
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
			return (check_single_dollar(str));
		free(var);
	}
	free(str);
	return (dest);
}

bool	check_dollar_signs(char *str, t_env *shell)
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
			if (check_dollar_signs(arr[i], shell))
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
