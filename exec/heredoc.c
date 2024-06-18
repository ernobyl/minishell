/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:16:30 by emichels          #+#    #+#             */
/*   Updated: 2024/06/18 19:15:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int g_heredoc_sig = 0;

static void	signal_heredoc(int sig)
{
	if (sig == SIGQUIT)
		g_heredoc_sig = 4;
	else if (sig == SIGINT)
	{
		g_heredoc_sig = 5;
		printf("\n");
	}
}

static void	parent_wait(int *fd, pid_t reader)
{
	int	status;

	close(fd[1]);
	waitpid(reader, &status, 0);
	if (g_heredoc_sig == 5 || 
        ((status) && WEXITSTATUS(status) == 130))
	{
        //close(fd[1]);
		close(fd[0]);
        g_exit_status = 130;
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
        //close(fd[1]);
    	close(fd[0]);
	}
}

void heredoc(char *limiter)
{
    pid_t reader;
    int fd[2];
    char *line;

    signal(SIGINT, signal_heredoc);
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
        exit_st(EXIT_SUCCESS);
    }
    else
    {
        // Parent process
        signal(SIGINT, signal_heredoc);
        parent_wait(fd, reader);
    }
}

// void heredoc(char *limiter)
// {
//     pid_t reader;
//     int fd[2];
//     char *line;

//     signal(SIGINT, signal_heredoc);
//     if (pipe(fd) == -1)
//     {
//         perror("pipe failed");
//         return;
//     }
//     reader = fork();
//     if (reader == -1)
//     {
//         perror("fork failed");
//         return;
//     }
//     if (reader == 0)
//     {
//         // Child process
//         close(fd[0]);
//         while (g_heredoc_sig != 4)
//         {
//             if (g_heredoc_sig == 5)
//             {
//                 line = NULL;
// 				exit(130);
//             }
//             line = readline("> ");
//             if (strncmp(line, limiter, strlen(limiter)) == 0)
//             {
//                 free(line);
//                 break ;
//             }
//             write(fd[1], line, strlen(line));
//             write(fd[1], "\n", 1);
//             free(line);
//         }
//         close(fd[1]);
//         exit(EXIT_SUCCESS);
//     }
//     else
//     {
//         // Parent process
//         //signal(SIGINT, signal_heredoc);
//         parent_wait(fd, reader);
//     }
// }
