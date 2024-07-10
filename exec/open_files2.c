/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:47:21 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/10 09:34:41 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static int	error_msg_fd2(char *str, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	return (code);
}

static int	infile_open2(char *file)
{
	int	file1;

	file1 = open(file, O_RDONLY);
	if (file1 == -1)
		return (error_msg_fd2(file, 1));
	dup2(file1, STDIN_FILENO);
	close(file1);
	return (0);
}

static int	outfile_open2(char *file, int type)
{
	int	file2;

	if (type == OUTFILE)
		file2 = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	else
		file2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (file2 == -1)
		return (error_msg_fd2(file, 1));
	dup2(file2, STDOUT_FILENO);
	close(file2);
	return (0);
}

int	open_files2(t_struct *token)
{
	t_struct	*temp;
	int			code;

	temp = token;
	while (temp && temp->index == token->index)
	{
		if (temp->type == HEREDOC)
			heredoc(token->value);
		if (temp->type == INFILE)
			code = infile_open2(temp->value);
		else if (temp->type == OUTFILE)
			code = outfile_open2(temp->value, OUTFILE);
		else if (temp->type == D_OUTFILE)
			code = outfile_open2(temp->value, D_OUTFILE);
		if (code == 1)
			return (1);
		temp = temp->next;
	}
	return (0);
}
