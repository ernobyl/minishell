/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:15:37 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/20 13:40:42 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parsing(char *input)
{
	char		**arr;
	char	*str;
	t_struct	token;

	str = validate_syntax(input);
	if (!str)
	{
		printf("Invalid syntax\n");
		return (false);
	}
	str = mod_str(ft_strtrim(str, " "));
	arr = split(str);
	if (!arr)
		return (false);
	arr = expand_env(arr);
	tokenize(&token, arr);
	return (true);
}
