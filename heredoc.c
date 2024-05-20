/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:16:30 by emichels          #+#    #+#             */
/*   Updated: 2024/05/20 10:19:57 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

void	heredoc(const char *delimiter)
{
	char	*line;
	char	buffer[1024];

	ft_bzero(buffer, 1024);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_strlcat(buffer, line, ft_strlen(line));
		ft_strlcat(buffer, "\n", 1);
		free(line);
	}
}
