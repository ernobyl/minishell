/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/07/09 09:49:13 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	check_export(char *new_var, int i)
{
	int	k;

	while (new_var[++i])
	{
		if (new_var[0] == '=')
			return (error_msg(" not a valid identifier", 1));
		else if (new_var[i] == '=')
			break ;
		else if (!ft_isalnum(new_var[i]))
			return (error_msg(" not a valid identifier", 1));
		k = 0;
		if (ft_isdigit(new_var[i]))
		{
			while (new_var[k])
			{
				if (ft_isalpha(new_var[k]))
					break ;
				if (!ft_isalpha(new_var[k]))
					k++;
				if (new_var[k] == '\0' || new_var[k] == '=')
					return (error_msg(" not a valid identifier", 1));
			}
		}
	}
	return (0);
}
