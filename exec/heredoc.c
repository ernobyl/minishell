/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:16:30 by emichels          #+#    #+#             */
/*   Updated: 2024/07/29 14:39:31 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/global.h"

static void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 5;
		printf("\n");
		exit(130);
	}
	g_signal = 0;
}

static void	parent_wait(int *fd, pid_t reader)
{
	int	status;

	close(fd[1]);
	waitpid(reader, &status, 0);
	if (g_signal == 5
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

static void	sig_exit_heredoc(int *fd)
{
	close(fd[1]);
	exit(130);
}

static void	heredoc_child(t_env *shell, int *fd, char *line, char **limiter)
{
	int	i;

	i = 0;
	close(fd[0]);
	while (!g_signal)
	{
		line = read_line();
		if (g_signal == 5)
			sig_exit_heredoc(fd);
		if (is_last_limiter(line, limiter, i, shell->k))
			break ;
		if (is_limiter(line, limiter, &i))
			continue ;
		if (i == shell->k - 1)
		{
			line = handle_expansion(line, shell);
			if (!line)
				exit(1);
			write_line_to_fd(fd[1], line);
		}
		free(line);
	}
	close(fd[1]);
}

void	heredoc(t_env *shell, char **limiter)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	signal(SIGINT, signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
	g_signal = 0;
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
		heredoc_child(shell, fd, line, limiter);
		ft_free(limiter);
		exit(EXIT_SUCCESS);
	}
	else
		parent_wait(fd, reader);
}
