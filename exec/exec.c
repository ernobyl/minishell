/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:37:57 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/14 15:59:38 by emichels         ###   ########.fr       */
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

static void	create_pipe(int token_index, int pipe_index, int *old_pipe_in)
{
	int	new_pipe[2];

	dup2(*old_pipe_in, STDIN_FILENO);
	if (*old_pipe_in != 0)
		close(*old_pipe_in);
	if (token_index == pipe_index)
		return ;
	pipe(new_pipe);
	dup2(new_pipe[1], STDOUT_FILENO);
	close(new_pipe[1]);
	*old_pipe_in = dup(new_pipe[0]);
	close(new_pipe[0]);
}

static void	create_child(char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		handle_error(1, "pid failed");
	if (pid == 0)
		execute(args[0], args, envp);
	waitpid(pid, &status, 0);
}

void	exec(t_struct *token, t_env *shell)
{
	char		**args;
	int			fd[2];
	int			old_pipe_in;

	old_pipe_in = 0;
	while (token)
	{
		save_fds(fd);
		create_pipe(token->index, shell->pipe, &old_pipe_in);
		args = parse_literals(token);
		if (token->type == HEREDOC)
			heredoc(token->value);
		open_files(token);
		if (run_builtin(args[0], args, shell) == 101)
			create_child(&args[0], shell->env);
		ft_free(args);
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->type == PIPE)
			token = token->next;
		restore_fds(fd);
	}
	close_fds(fd, old_pipe_in);
}
