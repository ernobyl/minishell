/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:16:30 by emichels          #+#    #+#             */
/*   Updated: 2024/07/09 10:58:21 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	g_heredoc_sig = 0;

static void	signal_heredoc(int sig)
{
	if (sig == SIGQUIT)
		g_heredoc_sig = 4;
	else if (sig == SIGINT)
	{
		g_heredoc_sig = 5;
		printf("\n");
		exit(130);
	}
	g_heredoc_sig = 0;
}

static void	parent_wait(int *fd, pid_t reader)
{
	int	status;

	close(fd[1]);
	waitpid(reader, &status, 0);
	if (g_heredoc_sig == 5
		|| ((status) && WEXITSTATUS(status) == 130))
	{
		close(fd[0]);
		exit(130);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

static void	heredoc_child(int *fd, char *line, char *limiter)
{
	close(fd[0]);
	while (!g_heredoc_sig)
	{
		line = readline("> ");
		if (g_heredoc_sig == 5)
		{
			close(fd[1]);
			exit(130);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close(fd[1]);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return ;
}

void	heredoc(char *limiter)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	signal(SIGINT, signal_heredoc);
	line = NULL;
	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		return ;
	}
	reader = fork();
	if (reader == -1)
	{
		perror("fork failed");
		return ;
	}
	if (reader == 0)
	{
		heredoc_child(fd, line, limiter);
		exit(EXIT_SUCCESS);
	}
	else
		parent_wait(fd, reader);
}
