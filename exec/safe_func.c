/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:44:03 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/07 22:48:27 by kmatjuhi         ###   ########.fr       */
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
