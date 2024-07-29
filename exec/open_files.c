/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:47:21 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/29 14:47:35 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static void	error_msg_fd(t_env *shell, t_struct *token, char *str, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	free_stack(token);
	ft_free(shell->env);
	ft_free(shell->args);
	free(shell->pids);
	exit(code);
}

static void	infile_open(t_env *shell, t_struct *token, char *file)
{
	int	file1;

	file1 = open(file, O_RDONLY);
	if (file1 == -1)
		error_msg_fd(shell, token, file, 1);
	dup2(file1, STDIN_FILENO);
	close(file1);
}

static void	outfile_open(t_env *shell, t_struct *token, char *file, int type)
{
	int	file2;

	if (type == OUTFILE)
		file2 = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	else
		file2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (file2 == -1)
		error_msg_fd(shell, token, file, 1);
	dup2(file2, STDOUT_FILENO);
	close(file2);
}

void	heredoc_open(t_env *shell, t_struct *token)
{
	t_struct	*temp;
	char		**limiter;
	int			i;

	shell->k = 0;
	i = 0;
	temp = token;
	while (temp && temp->index == token->index)
	{
		if (temp->type == HEREDOC)
			shell->k++;
		temp = temp->next;
	}
	if (shell->k == 0)
		return ;
	limiter = malloc(sizeof(char *) * (shell->k + 1));
	if (!limiter)
		exit(1);
	temp = token;
	while (temp && temp->index == token->index)
	{
		if (temp->type == HEREDOC)
			limiter[i++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	limiter[i] = NULL;
	heredoc(shell, limiter);
}

void	open_files(t_env *shell, t_struct *token)
{
	t_struct	*temp;

	temp = token;
	heredoc_open(shell, token);
	while (temp && temp->index == token->index)
	{
		if (temp->type == INFILE)
			infile_open(shell, token, temp->value);
		else if (temp->type == OUTFILE)
			outfile_open(shell, token, temp->value, OUTFILE);
		else if (temp->type == D_OUTFILE)
			outfile_open(shell, token, temp->value, D_OUTFILE);
		temp = temp->next;
	}
}
