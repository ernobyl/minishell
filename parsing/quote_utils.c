/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 08:36:24 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/09 19:39:55 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	skip_quotes(char *str, int i, char quote)
{
	while (str[i] && (str[i] != quote))
		i++;
	if ((str[i + 1] || str[i + 1] == '\0'))
		return (i + 1);
	printf("is -1");
	return (-1);
}

bool	matching_quote(char *str, int i, char quote)
{
	while (str[i] && (str[i] != quote))
		i++;
	if (str[i] != quote)
		return (false);
	return (true);
}

bool	ft_isquote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}
