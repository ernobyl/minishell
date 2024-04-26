/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:16:36 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/26 09:45:48 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isquote(char const *str, int i, char quote)
{
	while (str[i] != quote)
		i++;
	return (i);
}

static int	count_words(char const *s)
{
	int		i;
	int		rows;
	char	quote;

	i = 0;
	rows = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i++];
			i = ft_isquote(s, i, quote);
		}
		while (ft_isprint(s[i]))
			i++;
		while (s[i] == ' ')
			i++;
		rows++;
	}
	return (rows);
}

static int	count_letters(char const *s, int i, char c)
{
	int		count;
	char	quote;

	count = 0;
	if (s[i] == '"' || s[i] == '\'')
	{
		quote = s[i++];
		count = ft_isquote(s, i, quote);
		count = count - i + 2;
	}
	else
	{
		while (s[i] != c && s[i])
		{
			count++;
			i++;
		}
	}
	return (count);
}

static void	free_arr(char **dest, int i)
{
	while (i > 0)
	{
		i--;
		free(dest[i]);
	}
	free(dest);
}

static int	fill(char **dest, char const *s, char c, int rows)
{
	int			i;
	size_t		start;
	size_t		end;

	i = -1;
	start = 0;
	while (++i < rows)
	{
		while (s[start] == c)
			start++;
		end = count_letters(s, start, c);
		dest[i] = ft_substr(s, start, end);
		if (dest[i] == NULL)
		{
			free_arr(dest, i);
			return (0);
		}
		start = end + start;
	}
	return (1);
}

char	**split(char const *s)
{
	char	**dest;
	int		rows;

	rows = count_words(s);
	dest = (char **)malloc((rows + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	if (fill(dest, s, ' ', rows) == 0)
		return (NULL);
	dest[rows] = NULL;
	return (dest);
}
