/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:51:41 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/10 11:56:58 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	get_builtin_num(char *input)
{
	if (ft_strcmp("exit", input) == 0)
		return (EXIT);
	else if (ft_strcmp("pwd", input) == 0)
		return (PWD);
	else if (ft_strncmp("cd ", input, 3) == 0
		|| ft_strcmp("cd", input) == 0)
		return (CD);
	else if (ft_strcmp("echo", input) == 0
		|| ft_strncmp("echo -n", input, 7) == 0)
		return (ECHO);
	else if (ft_strcmp("export", input) == 0
		|| ft_strncmp("export ", input, 7) == 0)
		return (EXPORT);
	else if (ft_strcmp("unset", input) == 0)
		return (UNSET);
	else if (ft_strcmp("env", input) == 0)
		return (ENV);
	else
		return (NOT_BUILTIN);
}
