/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:30:19 by emichels          #+#    #+#             */
/*   Updated: 2024/07/08 11:44:44 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static void	wait_for_children(int *pids, int cmds_num)
{
	int	i;
	int	status;

	i = 0;
	while (i <= cmds_num)
	{
		waitpid(pids[i], &status, 0);
		g_exit_status = WEXITSTATUS(status);
		i++;
	}
	free(pids);
}

static t_struct	*next_cmd(t_struct *token)
{
	while (token && token->type != PIPE)
		token = token->next;
	if (token && token->type == PIPE)
		token = token->next;
	return (token);
}

void	exec_cmds(t_struct *token, t_env *shell)
{
	int		*pids;
	int		pipefd[2];
	int		fd[2];
	int		pipe_in;
	int		i;

	pipe_in = -1;
	i = 0;
	if (ft_strcmp(token->value, "\0") == 0)
		token = token->next;
	pids = ft_calloc(shell->cmds_num + 1, sizeof(int));
	while (token)
	{
		save_fds(fd);
		if (token->index != shell->cmds_num)
			safe_pipe(pipefd);
		pids[i++] = child(shell, token, &pipe_in, pipefd);
		token = next_cmd(token);
		restore_fds(fd, pipefd, &pipe_in);
	}
	safe_close(pipefd[0]);
	safe_close(pipefd[1]);
	close_fds(fd, pipe_in);
	wait_for_children(pids, shell->cmds_num);
}
