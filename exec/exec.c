/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:37:57 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/03 13:10:53 by kmatjuhi         ###   ########.fr       */
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
	while (temp && temp->index == token->index)
	{
		if (temp->token == LITERAL)
			i++;
		temp = temp->next;
	}
	args = malloc((i + 1) * sizeof(char *));
	i = 0;
	temp = token;
	while (temp && temp->index == token->index)
	{
		if (temp->token == LITERAL)
			args[i++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

static void	create_child(char *argv, char **envp, int *fd)
{
	pid_t	pid;

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

void	exec(t_struct *token, t_env *shell)
{
	char	**args;
	int 	fd[2];

	// print_nodes(token);
	while (token)
	{
		args = parse_literals(token);
		open_files(token, fd);
		create_child(args[0], shell->env, fd);
		while (token && token->token != PIPE)
			token = token->next;
		if (token && token->token == PIPE)
			token = token->next;
	}
}
