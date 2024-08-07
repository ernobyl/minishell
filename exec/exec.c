/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:30:19 by emichels          #+#    #+#             */
/*   Updated: 2024/08/07 21:38:49 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/global.h"

static void	wait_for_children(t_env *shell, int *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i <= shell->cmds_num)
	{
		waitpid(pids[i], &status, 0);
		shell->exit_code = WEXITSTATUS(status);
		i++;
	}
	free(pids);
}

static void	parent(t_env *shell, int *pids, int *fd, int pipe_in)
{
	close_fds(fd, pipe_in);
	wait_for_children(shell, pids);
}

static t_struct	*next_cmd(t_struct *token)
{
	while (token && token->type != PIPE)
		token = token->next;
	if (token && token->type == PIPE)
		token = token->next;
	return (token);
}

static bool	run_one_cmd(t_env *shell, t_struct *token)
{
	char	**args;

	shell->infile = "\0";
	shell->outfile = "\0";
	if (shell->cmds_num == 0)
	{
		if (ft_strcmp(token->value, "\0") == 0 && !token->next)
		{
			shell->exit_code = 0;
			return (true);
		}
		args = args_list(token);
		if (run_builtin(args[0], args, shell, token) != 101)
		{
			ft_free(args);
			return (true);
		}
		ft_free(args);
	}
	return (false);
}

void	exec_cmds(t_struct *token, t_env *shell)
{
	int		pipefd[2];
	int		fd[2];
	int		pipe_in;
	int		i;

	pipe_in = -1;
	i = 0;
	if (run_one_cmd(shell, token))
		return ;
	token = is_empty_token(token);
	shell->pids = ft_calloc(shell->cmds_num + 1, sizeof(int));
	if (!shell->pids)
		return ;
	while (token)
	{
		if (!set_fork_signal())
			return ;
		save_fds(fd);
		if (token->index != shell->cmds_num)
			safe_pipe(pipefd);
		shell->pids[i++] = child(shell, token, &pipe_in, pipefd);
		token = next_cmd(token);
		restore_fds(fd, pipefd, &pipe_in, shell->cmds_num);
	}
	parent(shell, shell->pids, fd, pipe_in);
}
