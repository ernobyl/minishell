/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:15:37 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/05 20:12:06 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

bool	parsing(char *input, t_env *shell)
{
	char		**arr;
	char		*str;

	str = validate_syntax(shell, input);
	if (!str)
		return (false);
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
	shell->token = tokenize(arr, shell, 0, 0);
	ft_free(arr);
	exec_cmds(shell->token, shell);
	free_stack(shell->token);
	return (true);
}
