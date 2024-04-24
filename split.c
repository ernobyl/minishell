/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:16:36 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/24 12:21:26 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip(char const *s, int i, char c)
{
	while (s[i] && s[i] != c)
	{
		printf("%c\n", s[i]);
		i++;
	}
	if (s[i] == '\0')
		return (-1);
	while (s[i] && s[i] == ' ')
		i++;
	return (i + 1);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] == c && s[i])
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		// if find "      i++ until finding" -> add a row to it . if no found closing. return false
		if (s[i] == '"')
		{
			printf("going into skip 1\n");
			i = skip(s, i + 1, '"');
			if (i == -1)
				return (0);
			j++;
		}
		if (s[i] == '\'')
		{
			printf("going into skip 2\n");
			i = skip(s, i + 1, '\'');
			if (i == -1)
				return (0);
			j++;
		}
		// else if '       i++ until finding ' -> add new row to it. if no found closing return false
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			printf("nadding row\n");
			j++;
		}
		i++;
	}
	return (j + 1);
}

static int	count_letters(char const *s, int i, char c)
{
	int	count;

	count = 0;
	while (s[i] != c && s[i])
	{
		count++;
		i++;
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

char	**split(char const *s, char c)
{
	char	**dest;
	int		rows;

	rows = count_words(s, c);
	printf("\namount rows %d\n", rows);
	dest = (char **)malloc((rows + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	// if (fill(dest, s, c, rows) == 0)
	// 	return (NULL);
	// dest[rows] = NULL;
	return (dest);
}
