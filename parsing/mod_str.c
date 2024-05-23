/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:13:50 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/21 09:06:26 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	count_extra_space(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_iswhitespace(str[i]))
			i++;
		if (ft_isquote(str[i]))
			i = skip_quotes(str, i + 1, str[i]);
		if (ft_isspecialchar(str[i]))
		{
			if (str[i - 1] != ' ')
				count++;
			if (str[i + 1] != ' ' && str[i + 1] != str[i])
				count++;
		}
		i++;
	}
	return (count);
}

static char	*add_extra_space(char *str, int count)
{
	char	*dest;
	char	sign;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str) + count));
	if (!dest)
		return (NULL);
	while (str[i])
	{
		if (ft_isquote(str[i]))
		{
			sign = str[i];
			dest[j++] = str[i++];
			while (str[i] && str[i] != sign)
				dest[j++] = str[i++];
			dest[j++] = str[i++];
		}
		if (ft_isspecialchar(str[i]))
		{
			sign = str[i];
			if (str[i - 1] != ' ')
				dest[j++] = ' ';
			while (str[i] == sign)
				dest[j++] = str[i++];
			if (str[i] != ' ')
				dest[j++] = ' ';
		}
		else
			dest[j++] = str[i++];
	}
	dest[j] = '\0';
	free(str);
	return (dest);
}
// echo|thiscmd $PATH >>in|ls wvae342 <dawda |<file checking "dwdwa"
char	*mod_str(char *str)
{
	char	*dest;
	int		count;

	count = count_extra_space(str);
	dest = add_extra_space(str, count);
	return (dest);
}
