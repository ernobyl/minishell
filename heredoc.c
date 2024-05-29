/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:16:30 by emichels          #+#    #+#             */
/*   Updated: 2024/05/29 09:13:17 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	parent_wait(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	wait(NULL);
}

void	heredoc(char *limiter)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		printf("error\n");
		exit(1);
	}
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while ((line = readline(NULL)) != NULL)
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
	}
	else
		parent_wait(fd);
}
