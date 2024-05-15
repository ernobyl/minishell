/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:15:37 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/14 11:33:56 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing(char *input)
{
	int			i;
	char		**arr;
	t_struct	token;

	i = 0;
	input = ft_strtrim(input, " ");
	if (!validate_syntax(input))
	{
		printf("Syntax error\n");
		return (FALSE);
	}
	arr = split(input);
	if (!arr)
		return (FALSE);
	arr = expand_env(arr);
	tokenize(&token, arr);
	return (TRUE);
}
