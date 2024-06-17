/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:13:50 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/17 14:46:19 by emichels         ###   ########.fr       */
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
	if (str[*i - 1] != ' ')
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
	dest = malloc(sizeof(char) * (ft_strlen(str) + count + 1));
	if (!dest)
		return (NULL);
	while (str[i])
	{
		if (ft_isquote(str[i]))
			handle_quotes(str, dest, &i, &j);
		if (ft_isspecialchar(str[i]))
			handle_special_chars(str, dest, &i, &j);
		else
			dest[j++] = str[i++];
	}
	dest[j] = '\0';
	free(str);
	return (dest);
}

char	*mod_str(char *str)
{
	char	*dest;
	int		count;

	count = count_extra_space(str);
	dest = add_extra_space(str, count);
	return (dest);
}
