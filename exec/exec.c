/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:37:57 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/29 13:51:20 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	error_msg_kim(char *str, int *fd, int code)
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
	dup2(fd[1], STDOUT_FILENO);
	// close(fd[0]);
	close(file1);
}

void	outfile_open(int *fd, char *file, int token)
{
	int	file2;

	printf("opening file %s\n", file);
	if (token == OUTFILE)
		file2 = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	else 
		file2 = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (file2 == -1)
		error_msg_kim(file, fd, 2);
	dup2(file2, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	// close(fd[1]);
	close(file2);
}

void	execute(char **argv, char **envp, int *fd)
{
	char	*path;
	int		i;

	path = env_path(argv[0], envp);
	if (!path)
	{
		i = -1;
		while (argv[++i])
			free(argv[i]);
		free(argv);
		handle_error(127, "command not found");
	}
	if (execve(path, argv, envp) == -1)
		handle_error(127, "command not found");
}

char	**parse_literals(t_struct *token)
{
	t_struct	*temp;
	char		**args;
	int			i;
	int count;

	i = 0;
	count = 0;
	temp = token;
	while (temp && temp->token != PIPE)
	{
		count++;
		temp = temp->next;
	}
	temp = token;
	args = (char **)malloc((count + 1) * sizeof(char *));
	while (temp && temp->token != PIPE)
	{
		if (temp->token == LITERAL)
			args[i++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

static void	create_child(char **argv, char **envp, int *fd)
{
	pid_t	pid;

	if (pipe(fd) == -1)
		handle_error(1, "pipe error");
	pid = fork();
	if (pid == -1)
		handle_error(1, "pid failed");
	if (pid == 0)
	{
		// close(fd[0]);
		dup2(fd[1], STDIN_FILENO);
		execute(argv, envp, fd);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	open_files(t_struct *token, int *fd)
{
	while (token)
	{
		if (token->token == INFILE)
			infile_open(fd, token->value);
		else if (token->token == OUTFILE)
			outfile_open(fd, token->value, OUTFILE);
		else if (token->token == D_OUTFILE)
			outfile_open(fd, token->value, D_OUTFILE);
		token = token->next;
	}
}

void	exec(t_struct *token, t_env *shell)
{
	char	**args;
	int 	fd[2];

	open_files(token, fd);
	while (token)
	{
		args = parse_literals(token);
		create_child(args, shell->env, fd);
		while (token && token->token != PIPE)
			token = token->next;
		if (token && token->token == PIPE)
			token = token->next;
	}
}
