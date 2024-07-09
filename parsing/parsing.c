/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:15:37 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/09 19:37:53 by kmatjuhi         ###   ########.fr       */
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
		printf("Invalid syntax\n");
		return (false);
	}
	str = add_space(ft_strtrim(str, " "));
	if (!str)
		return (false);
	arr = split(str);
	free(str);
	if (!arr)
		return (false);
	arr = expand_env(arr, shell);
	if (!arr)
		return (false);
	token = tokenize(arr, shell);
	exec_cmds(token, shell);
	ft_free(arr);
	// free whole token;
	free(token);
	return (true);
}
