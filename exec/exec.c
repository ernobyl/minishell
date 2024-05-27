/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:37:57 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/27 14:38:15 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	**parse_literals(t_struct *token)
{
	t_struct	*temp;
	char		**args;
	int			i;

	i = 0;
	temp = token;
	while (temp && temp->token != PIPE)
	{
		if (temp->token == LITERAL)
			args[i++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

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

void	open_files(t_struct *token)
{
	int	filein;
	int fileout;

	filein = 0;
	fileout = 0;
	while (token && token->token != PIPE)
	{
		if (token->token == INFILE)
			filein = open_file(token->value, 2);
		else if (token->token == OUTFILE)
			fileout = open_file(token->value, 1);
		else if (token->token == D_OUTFILE)
			fileout = open_file(token->value, 0);
	}
	if (filein)
		dup2(filein, STDIN_FILENO);
	if (fileout)
		dup2(fileout, STDOUT_FILENO);
	printf("%s", token->value);
}

void	exec(t_struct *token, t_env *shell)
{
	char	**args;
	int i;
	int outfile;
	while (token)
	{
		args = parse_literals(token);
		open_files(token);
		create_child(args, shell->env);
	}
}
