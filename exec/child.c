/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:36:51 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/10 14:38:02 by kmatjuhi         ###   ########.fr       */
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
	char	**args;

	args = args_list(token);
	if (!args)
		handle_error(1, "malloc failed");
	else
	{
		if (*pipe_in != -1)
		{
			dup2(*pipe_in, STDIN_FILENO);
			close(*pipe_in);
		}
		if (token->index != shell->cmds_num)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		open_files(token);
		if (run_builtin(args[0], args, shell, token) == 101)
			execute(args[0], args, shell->env);
		ft_free(args);
	}
	exit(shell->exit_code);
}

int	child(t_env *shell, t_struct *token, int *pipe_in, int *pipefd)
{
	int		pid;

	pid = safe_fork();
	if (pid == 0)
		run_cmds(shell, token, pipe_in, pipefd);
	return (pid);
}
