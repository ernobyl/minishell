/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:21:22 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/08 23:14:30 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static bool	is_exitcode(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$')
		i++;
	if (str[++i] == '?')
		return (true);
	return (false);
}

static char	*find_and_replace_exitcode(char *str, t_env *shell, int i)
{
	char	*exit_code;
	char	*dest;
	int		k;
	int		j;

	j = 0;
	k = 0;
	exit_code = ft_itoa(shell->exit_code);
	dest = malloc(ft_strlen(str) - 1 + ft_strlen(exit_code));
	if (!dest)
		return (NULL);
	while (str[i] != '$')
		dest[j++] = str[i++];
	if (str[++i] == '?')
	{
		i++;
		while (exit_code[k])
			dest[j++] = exit_code[k++];
	}
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	free(exit_code);
	return (dest);
}

char	*find_and_replace_env(char *str, char *replace, int len)
{
	int		i;
	int		k;
	int		j;
	int		n;
	char	*dest;

	i = 0;
	j = 0;
	k = 0;
	n = (ft_strlen(str) + ft_strlen(replace) - len);
	dest = malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	while (str[i] && str[i] != '$')
		dest[j++] = str[i++];
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		i++;
	while (replace[k])
		dest[j++] = replace[k++];
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	return (dest);
}

static char	*find_and_replace_literal(char *str)
{
	char	*var;
	char	*dest;
	int		len;

	var = find_variable(str);
	if (!var)
		return (NULL);
	len = ft_strlen(var) - 1;
	dest = find_and_replace_env(str, "", len);
	free(var);
	return (dest);
}

static char	*is_single_dollar(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i + 1] == ' ' || str[i + 1] == '\0' || \
	(i > 0 && (str[i + 1] == '"' && str[i - 1] == '"')))
		return (str);
	if (str[i + 1] == '\'')
	{
		new = new_str(str);
		if (!new)
			return (NULL);
	}
	else
		new = find_and_replace_literal(str);
	free(str);
	return (new);
}

char	*expand_str(char *str, t_env *shell)
{
	char		*dest;
	char		*var;
	int			i;
	int			len;

	if (is_exitcode(str))
		dest = find_and_replace_exitcode(str, shell, 0);
	else
	{
		var = find_variable(str);
		if (!var)
			return (NULL);
		len = ft_strlen(var) - 1;
		i = find_env_var(shell, var);
		if (i != -1)
		{
			dest = find_and_replace_env(str, ft_strchr_next \
			(shell->env[i], '='), len);
		}
		else
			return (is_single_dollar(str));
	}
	free(str);
	return (dest);
}
