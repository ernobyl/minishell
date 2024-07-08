/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:30:19 by emichels          #+#    #+#             */
/*   Updated: 2024/07/08 11:01:30 by kmatjuhi         ###   ########.fr       */
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

static int	child(char **args, t_env *shell, t_struct *token, int *pipe_in, int *pipefd)
{
	int	pid;

	pid = safe_fork();
	if (pid == 0)
	{
		if (*pipe_in != -1)
		{
			dup2(*pipe_in, STDIN_FILENO);
			close(*pipe_in);
		}
		if (token->index != shell->pipe)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		if (token->type == HEREDOC)
			heredoc(token->value);
		open_files(token);
		if (run_builtin(args[0], args, shell, token) == 101)
			execute(args[0], args, shell->env);
		exit(g_exit_status);
	}
	return (pid);
}

void	wait_for_children(int *pids, int amount)
{
	int	i;
	int	status;

	i = 0;
	while (i <= amount)
	{
		waitpid(pids[i], &status, 0);
		g_exit_status = WEXITSTATUS(status);
		i++;
	}
	free(pids);
}

void	exec_cmds(t_struct *token, t_env *shell)
{
	char	**args;
	int		pipe_in;
	int		pipefd[2];
	int		fd[2];
	int		*pids;
	int		i;

	pipe_in = -1;
	i = 0;
	if (ft_strcmp(token->value, "\0") == 0)
		token = token->next;
	pids = ft_calloc(shell->pipe + 1, sizeof(int));
	while (token)
	{
		save_fds(fd);
		if (token->index != shell->pipe)
			safe_pipe(pipefd);
		args = parse_literals(token);
		pids[i++] = child(&args[0], shell, token, &pipe_in, pipefd);
		ft_free(args);
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->type == PIPE)
			token = token->next;
		restore_fds(fd, pipefd, &pipe_in);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close_fds(fd, pipe_in);
	wait_for_children(pids, shell->pipe);
}
