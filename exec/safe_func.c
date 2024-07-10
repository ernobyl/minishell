/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:44:03 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/10 22:15:03 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	safe_pipe(int *fd)
{
	if (pipe(fd) == -1)
		handle_error(1, "pipe failed");
}

int	safe_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		handle_error(1, "fork failed");
	return (pid);
}

void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	safe_dup2(int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
		handle_error(1, "dup2 failed");
	safe_close(fd);
}
