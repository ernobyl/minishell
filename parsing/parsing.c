/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:15:37 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/06 13:32:27 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing(char *input)
{
	t_struct	*cmd;
	int			i;
	char		**arr;
	t_stack		*token;

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
	tokenize(arr, &token);
	ft_free(arr);
	return (TRUE);
}
