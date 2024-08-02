/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:47:21 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/02 08:31:29 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*infile_open2(char *file)
{
	int	file1;

	file1 = open(file, O_RDONLY);
	if (file1 == -1)
	{
		error_msg_fd2(file, 1);
		return (NULL);
	}
	close(file1);
	return (file);
}

static char	*outfile_open2(char *file, int type)
{
	int	file2;

	if (type == OUTFILE)
		file2 = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	else
		file2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (file2 == -1)
	{
		error_msg_fd2(file, 1);
		return (NULL);
	}
	close(file2);
	return (file);
}

static int	reopen_files(char *infile, char *outfile, int type)
{
	int	fd;

	if (infile != NULL && (ft_strcmp(infile, "\0") != 0))
	{
		fd = open(infile, O_RDONLY);
		if (fd == -1)
			return (error_msg_fd2(infile, 1), 1);
		safe_dup2(fd, STDIN_FILENO);
	}
	if (outfile != NULL && (ft_strcmp(outfile, "\0") != 0))
	{
		if (type == OUTFILE)
			fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		else
			fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (fd == -1)
			return (error_msg_fd2(outfile, 1), 1);
		safe_dup2(fd, STDOUT_FILENO);
	}
	return (0);
}

void	xcute_hd(t_env *shell)
{
	if (count_heredoc(shell->token) != 0)
	{
		infile_open2(shell->hd_name);
		unlink(shell->hd_name);
		free(shell->hd_name);
	}
}

int	open_files2(t_env *shell, t_struct *token)
{
	t_struct	*temp;
	int			file_type;

	temp = token;
	xcute_hd(shell);
	while (temp && temp->index == token->index)
	{
		if (temp->type == INFILE)
			shell->infile = infile_open2(temp->value);
		else if (temp->type == OUTFILE)
		{
			shell->outfile = outfile_open2(temp->value, OUTFILE);
			file_type = OUTFILE;
		}
		else if (temp->type == D_OUTFILE)
		{
			shell->outfile = outfile_open2(temp->value, D_OUTFILE);
			file_type = D_OUTFILE;
		}
		if (shell->infile == NULL || shell->outfile == NULL)
			return (1);
		temp = temp->next;
	}
	return (reopen_files(shell->infile, shell->outfile, file_type));
}
