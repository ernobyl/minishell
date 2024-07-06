/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:30:19 by emichels          #+#    #+#             */
/*   Updated: 2024/07/06 13:49:11 by kmatjuhi         ###   ########.fr       */
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
		if (temp->type == LITERAL)
			i++;
		temp = temp->next;
	}
	args = malloc((i + 1) * sizeof(char *));
	i = 0;
	temp = token;
	while (temp && temp->index == token->index)
	{
		if (temp->type == LITERAL)
			args[i++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

static int	create_child(char **args, t_env *shell, t_struct *token, int *pipe_in, int *pipefd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		handle_error(1, "fork failed");
	if (pid == 0)
	{
		if (*pipe_in != -1)
			dup2(*pipe_in, STDIN_FILENO);
		if (token->index != shell->pipe)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
		}
		if (token->type == HEREDOC)
			heredoc(token->value);
		open_files(token);
		if (run_builtin(args[0], args, shell, token) == 101)
		{
			execute(args[0], args, shell->env);
			close(pipefd[1]);
			close(pipefd[0]);
		}
	}
	return (pid);
}

void wait_for_children(int *pids, int amount)
{
	int i;
	int status;

	i = 0;
	while (i <= amount)
	{
		waitpid(pids[i], &status, 0);
		if (WEXITSTATUS(status) != 0)
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	exec(t_struct *token, t_env *shell)
{
	char	**args;
	int		pipe_in;
	int		pipefd[2];
	int		*pids;

	pipe_in = -1;
	args = parse_literals(token);
	if (shell->pipe == 0 && run_builtin(args[0], args, shell, token) != 101)
		return ;
	pids = ft_calloc(shell->pipe + 1, sizeof(int));
	while (token)
	{
		if (token->index != shell->pipe)
		{
			if (pipe(pipefd) == -1)
				handle_error(1, "pipe failed");
		}
		args = parse_literals(token);
		create_child(&args[0], shell, token, &pipe_in, pipefd);
		close(pipefd[1]);
		pipe_in = dup(pipefd[0]);
		close(pipefd[0]);
		ft_free(args);
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->type == PIPE)
			token = token->next;
	}
	if (pipe_in != -1)
		close(pipe_in);
	close(pipefd[0]);
	close(pipefd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	wait_for_children(pids, shell->pipe);
}
