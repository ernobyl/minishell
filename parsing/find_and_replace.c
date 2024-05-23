/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:02:48 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/20 14:32:52 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	*find_and_replace(char *str, char *replace, int len)
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