/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:02:48 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/15 11:07:41 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*find_and_replace(char *str, char *replace)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	// fixa skitet
	printf("{%s}\n", str);
	// while (str[i] && str[i] != '$')
	// 	dest[j++] = str[i++];
	// while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
	// 	i++;
	// while (str[i])
	// 	dest[j++] = str[i++];
	// dest[j] = '\0';
	// printf("%s\n", dest);
	return ("HELLO");
}