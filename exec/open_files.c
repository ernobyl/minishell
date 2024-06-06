/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:47:21 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/06 15:18:51 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static void	error_msg_kim(char *str, int *fd, int code)
{
	close(fd[0]);
	close(fd[1]);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	exit(code);
}

void	infile_open(int *fd, char *file)
{
	int	file1;

	file1 = open(file, O_RDONLY);
	if (file1 == -1)
		error_msg_kim(file, fd, 126);
	dup2(file1, STDIN_FILENO);
	close(file1);
}

void	outfile_open(int *fd, char *file, int token)
{
	int	file2;

	if (token == OUTFILE)
		file2 = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	else 
		file2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (file2 == -1)
		error_msg_kim(file, fd, 2);
	dup2(file2, STDOUT_FILENO);
	close(file2);
}

void	open_files(t_struct *token, int *fd)
{
	int		index;
	t_struct *temp;

	temp = token;
	while (temp && temp->index == token->index)
	{
		if (temp->token == INFILE)
			infile_open(fd, temp->value);
		else if (temp->token == OUTFILE)
		{
			outfile_open(fd, temp->value, OUTFILE);
		}
		else if (temp->token == D_OUTFILE)
			outfile_open(fd, temp->value, D_OUTFILE);
		temp = temp->next;
	}
}