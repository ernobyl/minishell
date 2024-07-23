/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:12:41 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/23 21:59:57 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	save_fds(int *fd)
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}

void	restore_fds(int *fd, int *pipefd, int *pipe_in, int cmds)
{
	safe_close(*pipe_in);
	if (cmds != 0)
	{
		safe_close(pipefd[1]);
		*pipe_in = dup(pipefd[0]);
		safe_close(pipefd[0]);
	}
	safe_dup2(fd[0], STDIN_FILENO);
	safe_dup2(fd[1], STDOUT_FILENO);
}

void	close_fds(int *fd, int pipe_in)
{
	if (pipe_in != -1)
		safe_dup2(pipe_in, STDIN_FILENO);
	safe_close(fd[0]);
	safe_close(fd[1]);
}
