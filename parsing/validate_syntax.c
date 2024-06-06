/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:03:50 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/06 23:57:59 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

bool	ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	return (false);
}

bool	ft_isspecialchar(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	validate_correct(char *str, int i, char sign)
{
	if (sign == '|' && str[i + 1] == '|')
		return (false);
	else if (sign == '<' || sign == '>')
	{
		if (str[i + 1] == sign && str[i + 2] == sign)
			return (false);
	}
	return (true);
}

int	validate_specialchar(char *str, int i, char sign)
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

char	*validate_syntax(char *str)
{
	int	i;

	i = 0;
	str = ft_strtrim(str, " ");
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (ft_isquote(str[i]))
		{
			if (!matching_quote(str, i + 1, str[i]))
				return (NULL);
			i = skip_quotes(str, i + 1, str[i]);
		}
		else if (ft_isspecialchar(str[i]))
		{
			i = validate_specialchar(str, i, str[i]);
			if (i == -1 || str[i] == '\0')
				return (NULL);
		}
		else
			i++;
	}
	return (str);
}
