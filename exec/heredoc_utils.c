/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:37:07 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/06 11:11:08 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

bool	is_last_limiter(char *line, char **limiter, int i, int k)
{
	if (ft_strcmp(line, limiter[i]) == 0 && i == k - 1)
	{
		free(line);
		return (true);
	}
	return (false);
}

bool	is_limiter(char *line, char **limiter, int *i)
{
	if (ft_strcmp(line, limiter[*i]) == 0)
	{
		(*i)++;
		free(line);
		return (true);
	}
	return (false);
}

char	*handle_expansion(char *line, t_env *shell)
{
	while (ft_strchr(line, '$'))
	{
		line = expand_str(line, shell);
		if (!line)
			return (NULL);
		if (expanded_all(line, shell))
			break ;
	}
	return (line);
}

void	write_line_to_fd(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}
