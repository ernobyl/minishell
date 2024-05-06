/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:13:02 by emichels          #+#    #+#             */
/*   Updated: 2024/05/06 15:00:00 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**init_env_list(void)
{
	char	**env;
	int		len;
	int		i;
	int		var_len;
	
	len = 0;
	while (environ[len])
		len++;
	env = (char **)malloc((len + 1) * sizeof(char *));
	if (env == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		var_len = ft_strlen(environ[i]) + 1;
		env[i] = malloc(var_len);
		if (env[i] == NULL)
		{
			ft_free(env);
			return (NULL);
		}
		ft_memcpy(env[i], environ[i], var_len);
		i++;
	}
	env[len] = NULL;
	return (env);
}
