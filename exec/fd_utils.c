/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:12:41 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/08 10:59:58 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	save_fds(int *fd)
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}

void	restore_fds(int *fd, int *pipefd, int *pipe_in)
{
	close(pipefd[1]);
	*pipe_in = dup(pipefd[0]);
	close(pipefd[0]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	close_fds(int *fd, int old_pipe_in)
{
	if (old_pipe_in != -1)
	{
		dup2(old_pipe_in, STDOUT_FILENO);
		close(old_pipe_in);
	}
	close(fd[0]);
	close(fd[1]);
}
