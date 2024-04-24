/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:15:37 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/24 12:06:11 by kmatjuhi         ###   ########.fr       */
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
	arr = split(input, ' ');
	if (!arr)
		return (0);
	// while (arr[i])
	// {
	// 	printf("%s\n", arr[i]);
	// 	i++;
	// }
	return (1);
}
