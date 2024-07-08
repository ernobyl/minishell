/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:16:36 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/08 13:04:56 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	count_words(char *s)
{
	int		rows;
	int		i;

	i = 0;
	rows = 0;
	while (s[i])
	{
		while (ft_isprint(s[i]))
		{
			if (ft_isquote(s[i]))
				i = skip_quotes(s, i + 1, s[i]);
			else
				i++;
		}
		while (ft_iswhitespace(s[i]))
			i++;
		rows++;
	}
	return (rows);
}

static int	count_letters(char *s, int i)
{
	int		count;

	count = i;
	while (ft_isprint(s[i]))
	{
		if (ft_isquote(s[i]))
			i = skip_quotes(s, i + 1, s[i]);
		else
			i++;
	}
	count = i - count;
	return (count);
}

static bool	fill(char **dest, char *s, char c, int rows)
{
	size_t		start;
	size_t		end;
	int			i;

	i = -1;
	start = 0;
	while (++i < rows)
	{
		while (s[start] == c)
			start++;
		end = count_letters(s, start);
		dest[i] = ft_substr(s, start, end);
		if (dest[i] == NULL)
		{
			ft_free(dest);
			return (false);
		}
		start = end + start;
	}
	return (true);
}

char	**split(char *s)
{
	char	**dest;
	int		rows;

	rows = count_words(s);
	dest = (char **)malloc((rows + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	if (!fill(dest, s, ' ', rows))
		return (NULL);
	dest[rows] = NULL;
	return (dest);
}
