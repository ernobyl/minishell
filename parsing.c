/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:15:37 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/24 08:48:27 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *input)
{
	char	**arr;
	int		i;
	t_struct *cmd;
	t_struct *file;

	i = 0;
	arr = ft_split(input, ' ');
	if (!arr)
		return (0);
	while (arr[i])
	{
		// if find < or > or << or >>
		printf("%s\n", arr[i]);
		i++;
	}
	return (1);
}
