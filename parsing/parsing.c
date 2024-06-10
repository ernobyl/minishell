/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:15:37 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/10 21:12:26 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

bool	parsing(char *input, t_env *shell)
{
	t_struct	*token;
	char		**arr;
	char		*str;

	str = validate_syntax(input);
	if (!str)
	{
		free(str);
		free(input);
		printf("Invalid syntax\n");
		return (false);
	}
	str = mod_str(ft_strtrim(str, " "));
	arr = split(str);
	free(str);
	if (!arr)
		return (false);
	arr = expand_env(arr, shell);
	// token = tokenize(arr, shell);
	// exec(token, shell);
	ft_free(arr);
	return (true);
}
