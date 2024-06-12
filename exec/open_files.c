/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:47:21 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/12 13:39:24 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static void	error_msg_fd(char *str, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	exit(code);
}

static void	infile_open(char *file)
{
	int	file1;

	file1 = open(file, O_RDONLY);
	if (file1 == -1)
		error_msg_fd(file, 0);
	dup2(file1, STDIN_FILENO);
	close(file1);
}

static void	outfile_open(char *file, int type)
{
	int	file2;

	if (type == OUTFILE)
		file2 = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	else 
		file2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (file2 == -1)
		error_msg_fd(file, 0);
	dup2(file2, STDOUT_FILENO);
	close(file2);
}

void	open_files(t_struct *token)
{
	t_struct	*temp;

	temp = token;
	while (temp && temp->index == token->index)
	{
		if (temp->type == INFILE)
			infile_open(temp->value);
		else if (temp->type == OUTFILE)
			outfile_open(temp->value, OUTFILE);
		else if (temp->type == D_OUTFILE)
			outfile_open(temp->value, D_OUTFILE);
		// else if (temp->token == HEREDOC)
		// 	heredoc(skip_set(input, "<<"));
		temp = temp->next;
	}
}
