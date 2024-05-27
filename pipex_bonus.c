/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:40 by emichels          #+#    #+#             */
/*   Updated: 2024/05/27 14:37:08 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	create_child(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		handle_error(1, "pipe error");
	pid = fork();
	if (pid == -1)
		handle_error(1, "pid failed");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int	i;
// 	int	filein;
// 	int	fileout;

// 	if (argc >= 5)
// 	{
// 		i = 2;
// 		fileout = open_file(token->value, 1);
// 		filein = open_file(token->value, 2);
// 		dup2(filein, STDIN_FILENO);
// 		while (i < argc - 2)
// 			create_child(argv[i++], envp);
// 		dup2(fileout, STDOUT_FILENO);
// 		execute(argv[argc - 2], envp);
// 	}
// 	input_error();
// }