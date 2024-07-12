/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:03:50 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/12 12:58:08 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static bool	validate_correct(char *str, int i, char sign)
{
	if (sign == '|' && str[i + 1] == '|')
		return (false);
	else if (sign == '<' || sign == '>')
	{
		if ((str[i + 1] == sign && str[i + 2] == sign) || (str[i] == '<' && str[i + 1] == '|'))
			return (false);
	}
	return (true);
}

static int	validate_specialchar(char *str, int i, char sign)
{
	int	count;

	count = 0;
	if (!validate_correct(str, i, sign))
		return (-1);
	while (str[i] && (str[i] == sign || str[i] == ' '))
	{
		if (str[i] == sign)
			count++;
		i++;
	}
	if (sign == '|' && count > 1)
		return (-1);
	else if (count > 2)
		return (-1);
	return (i);
}

static char	*validate_syntax2(char *str, int i)
{
	while (str[i])
	{
		while (str[i] && ft_iswhitespace(str[i]))
			i++;
		if (str[i] && ft_isquote(str[i]))
		{
			if (str[i + 1] && !matching_quote(str, i + 1, str[i]))
				return (NULL);
			i = skip_quotes(str, i + 1, str[i]);
			if (i == -1)
				return (NULL);
			if (str[i] && str[i] == '\0')
				break ;
		}
		else if (ft_isspecialchar(str[i]))
		{
			if (i == 0)
				return (NULL);
			i = validate_specialchar(str, i, str[i]);
			if (i == -1 || str[i] == '\0')
				return (NULL);
		}
		else
			i++;
	}
	return (str);
}

char	*validate_syntax(t_env *shell, char *str)
{
	int	i;

	i = 0;
	str = ft_strtrim(str, " ");
	if (!str)
		return (NULL);
	str = validate_syntax2(str, i);
	if (!str)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		shell->exit_code = 258;
	}
	return (str);
}
