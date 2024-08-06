/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:13:50 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/06 13:56:54 by kmatjuhi         ###   ########.fr       */
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
		if (str[i] && ft_isspecialchar(str[i]))
		{
			if (i > 0 && str[i - 1] != ' ')
				count++;
			if (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != str[i])
				count++;
		}
		if (str[i] && ft_isquote(str[i]))
			i = skip_quotes(str, i + 1, str[i]);
		if (i == -1)
			return (-1);
		if (str[i] != '\0' && str[i] != '"')
			i++;
	}
	return (count);
}

static void	handle_quotes(char *str, char *dest, int *i, int *j)
{
	char	sign;

	sign = str[*i];
	dest[(*j)++] = str[(*i)++];
	while (str[*i] && str[*i] != sign)
		dest[(*j)++] = str[(*i)++];
	dest[(*j)++] = str[(*i)++];
}

static void	handle_special_chars(char *str, char *dest, int *i, int *j)
{
	char	sign;

	sign = str[*i];
	if (*i > 0 && str[*i - 1] != ' ')
		dest[(*j)++] = ' ';
	while (str[*i] == sign)
		dest[(*j)++] = str[(*i)++];
	if (str[*i] != ' ')
		dest[(*j)++] = ' ';
}

static char	*add_extra_space(char *str, int count)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str) + count + 2));
	if (!dest)
		return (NULL);
	while (str[i])
	{
		if (str[i] && ft_isquote(str[i]))
			handle_quotes(str, dest, &i, &j);
		if (str[i] && ft_isquote(str[i]))
			continue ;
		if (str[i] && ft_isspecialchar(str[i]))
			handle_special_chars(str, dest, &i, &j);
		else if (str[i])
			dest[j++] = str[i++];
	}
	dest[j] = '\0';
	free(str);
	return (dest);
}

char	*add_space(char *str)
{
	char	*dest;
	int		count;

	count = count_extra_space(str);
	if (count == -1)
		return (NULL);
	dest = add_extra_space(str, count);
	if (!dest)
		free(str);
	return (dest);
}
