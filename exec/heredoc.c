/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:16:30 by emichels          #+#    #+#             */
/*   Updated: 2024/06/10 11:21:42 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static void	parent_wait(int *fd, pid_t reader)
{
	int	status;

	close(fd[1]);
	waitpid(reader, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
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

void heredoc(char *limiter)
{
    pid_t reader;
    int fd[2];
    char *line;

    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        return;
    }
    reader = fork();
    if (reader == -1)
    {
        perror("fork failed");
        return;
    }
    if (reader == 0)
    {
        // Child process
        close(fd[0]);
        while ((line = readline("> ")) != NULL)
        {
            if (g_signal_flag != 0)
				exit(130);
            if (strncmp(line, limiter, strlen(limiter)) == 0)
            {
                free(line);
                break ;
            }
            write(fd[1], line, strlen(line));
            write(fd[1], "\n", 1);
            free(line);
        }
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        // Parent process
        signal(SIGINT, handle_signal);
        parent_wait(fd, reader);
    }
}
