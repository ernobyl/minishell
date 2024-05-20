/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:20:45 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/20 13:43:27 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_struct *tokenize(t_struct *token, char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		printf("%s\n", arr[i++]);
	printf("done printing\n");
}