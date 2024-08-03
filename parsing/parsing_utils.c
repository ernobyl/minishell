/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:48:38 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/04 01:08:43 by kmatjuhi         ###   ########.fr       */
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

char	*ft_strchr_next(const char *s, int c)
{
	while (*s && (char)c != *s)
		s++;
	if ((char)c == *s)
		return ((char *)s + 1);
	return (0);
}

char	*new_str(char *str)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	new = malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	len = 1;
	while (str[len])
		new[i++] = str[len++];
	new[i] = '\0';
	return (new);
}
