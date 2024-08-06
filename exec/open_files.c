/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:47:21 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/06 13:03:30 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	*infile_open(char *file)
{
	int	file1;

	file1 = open(file, O_RDONLY);
	if (file1 == -1)
	{
		error_msg_fd(file, 1);
		return (NULL);
	}
	close(file1);
	return (file);
}

static char	*outfile_open(char *file, int type)
{
	int	file2;

	if (type == OUTFILE)
		file2 = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	else
		file2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (file2 == -1)
	{
		error_msg_fd(file, 1);
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
			return (error_msg_fd(infile, 1), 1);
		safe_dup2(fd, STDIN_FILENO);
	}
	if (outfile != NULL && (ft_strcmp(outfile, "\0") != 0))
	{
		if (type == OUTFILE)
			fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		else
			fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (fd == -1)
			return (error_msg_fd(outfile, 1), 1);
		safe_dup2(fd, STDOUT_FILENO);
	}
	return (0);
}

static int	xcute_hd(t_env *shell, t_struct *token)
{
	int	file1;
	int	error;

	error = 0;
	if (count_heredoc(token) != 0)
	{
		file1 = open(shell->hd_name, O_RDONLY);
		if (file1 == -1)
			error = error_msg_fd(shell->hd_name, 1);
		if (error == 0)
			safe_dup2(file1, STDIN_FILENO);
		if (token->index == shell->cmds_num)
			unlink(shell->hd_name);
	}
	if (error != 0)
		return (1);
	return (0);
}

int	open_files(t_env *shell, t_struct *token)
{
	t_struct	*temp;
	int			file_type;

	temp = token;
	if (xcute_hd(shell, token))
		return (1);
	while (temp && temp->index == token->index)
	{
		if (temp->type == INFILE)
			shell->infile = infile_open(temp->value);
		else if (temp->type == OUTFILE)
		{
			shell->outfile = outfile_open(temp->value, OUTFILE);
			file_type = OUTFILE;
		}
		else if (temp->type == D_OUTFILE)
		{
			shell->outfile = outfile_open(temp->value, D_OUTFILE);
			file_type = D_OUTFILE;
		}
		if (shell->infile == NULL || shell->outfile == NULL)
			return (1);
		temp = temp->next;
	}
	return (reopen_files(shell->infile, shell->outfile, file_type));
}
