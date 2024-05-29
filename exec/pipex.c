/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:06:33 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/29 10:56:18 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	infile_open(int *fd, char *file)
{
	int	file1;

	file1 = open(file, O_RDONLY);
	if (file1 == -1)
		error_msg_kim(file, fd, 126);
	dup2(file1, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(file1);
}

void	outfile_open(int *fd, char *file)
{
	int	file2;

	file2 = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (file2 == -1)
		error_msg_kim(file, fd, 2);
	dup2(file2, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(file2);
}

void	xcute_cmd(char *cmd, char **envp, int *fd)
{
	char	**args;
	char	**path;
	int		i;

	i = 0;
	args = parsing_args(cmd, fd);
	path = parsing_path(envp, args[0], fd);
	while (path[i])
	{
		if (access(path[i], F_OK) == -1)
			i++;
		else
		{
			if (access(path[i], X_OK) == -1)
			{
				ft_free_arr(path);
				ft_free_arr(args);
				custom_msg(path[i], "Permission denied\n", fd, 1);
			}
			execve(path[i], args, envp);
		}
	}
	ft_free_arr(path);
	ft_free_arr(args);
	custom_msg(cmd, ": Command not found\n", fd, 1);
}

void	pipex(char *argv[], char *envp[], int *fd)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		error_msg("", fd, 1);
	if (pid1 == 0)
	{
		infile_open(fd, argv[1]);
		xcute_cmd(argv[2], envp, fd);
	}
	pid2 = fork();
	if (pid2 == -1)
		error_msg("", fd, 1);
	if (pid2 == 0)
	{
		outfile_open(fd, argv[4]);
		xcute_cmd(argv[3], envp, fd);
	}
	close(fd[1]);
	close(fd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
