/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:13:02 by emichels          #+#    #+#             */
/*   Updated: 2024/05/23 10:53:44 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static char	**free_return(char **env)
{
	ft_free(env);
	return (NULL);
}

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
			return (free_return(env));
		ft_memcpy(env[i], environ[i], var_len);
		i++;
	}
	env[len] = NULL;
	return (env);
}
