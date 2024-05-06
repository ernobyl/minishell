/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:03:50 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/06 13:11:31 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	validate_syntax(char *input)
{
	int		i;
	char	sign;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && ((input[i + 1] == '|') || input[i + 1] == '\0'))
			return (FALSE);
		if (input[i] == '"' || input[i] == '\'')
		{
			sign = input[i++];
			while (input[i] && input[i] != sign)
				i++;
			if (input[i] != sign)
				return (FALSE);
		}
		if (input[i] == '<' && ((input[i + 1] == '<' && input[i + 2] == '<') \
		|| input[i + 1] == '\0'))
			return (FALSE);
		if (input[i] == '>' && ((input[i + 1] == '>' && input[i + 2] == '>') \
		|| input[i + 1] == '\0'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
