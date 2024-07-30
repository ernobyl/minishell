/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:36:51 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/31 02:36:13 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char	**args_list(t_struct *token)
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
	if (!args)
		return (NULL);
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

static void	run_cmds(t_env *shell, t_struct *token, int *pipe_in, int *pipefd)
{
	shell->args = args_list(token);
	if (!shell->args)
		handle_error(1, "malloc failed");
	else
	{
		if (*pipe_in != -1)
			safe_dup2(*pipe_in, STDIN_FILENO);
		if (token->index != shell->cmds_num)
		{
			close(pipefd[0]);
			safe_dup2(pipefd[1], STDOUT_FILENO);
		}
		open_files(shell, token);
		if (run_builtin(shell->args[0], shell->args, shell, token) == 101)
		{
			free_stack(token);
			execute(shell, shell->args[0], shell->args, shell->env);
		}
		ft_free(shell->args);
		ft_free(shell->env);
		free(shell->pids);
	}
	exit(shell->exit_code);
}

int	count_heredoc(t_struct *token)
{
	t_struct	*temp;
	int			i;

	i = 0;
	temp = token;
	while (temp && temp->index == token->index)
	{
		if (temp->type == HEREDOC)
			i++;
		temp = temp->next;
	}
	return (i);
}

int	child(t_env *shell, t_struct *token, int *pipe_in, int *pipefd)
{
	int		pid;

	heredoc_open(shell, token);
	if (g_signal == 5)
		return (0);
	pid = safe_fork();
	if (pid == 0)
		run_cmds(shell, token, pipe_in, pipefd);
	return (pid);
}
