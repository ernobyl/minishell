/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:37:07 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/24 11:25:16 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*read_line(void)
{
	return (readline("> "));
}

bool	is_last_limiter(char *line, char **limiter, int i, int k)
{
	if (ft_strncmp(line, limiter[i], ft_strlen(limiter[i])) == 0 && i == k - 1)
	{
		free(line);
		return (true);
	}
	return (false);
}

bool	is_limiter(char *line, char **limiter, int *i)
{
	if (ft_strncmp(line, limiter[*i], ft_strlen(limiter[*i])) == 0)
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
