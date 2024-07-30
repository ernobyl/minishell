/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:36:51 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/29 15:44:54 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/global.h"
// void print_open_fds() {
//     int fd;
//     char path[256];
//     char buf[1024];
//     ssize_t len;
    
//     printf("Open file descriptors:\n");
//     for (fd = 0; fd < 1024; fd++) { // Typically, file descriptors range from 0 to 1023
//         snprintf(path, sizeof(path), "/proc/self/fd/%d", fd);
//         len = readlink(path, buf, sizeof(buf) - 1);
//         if (len != -1) {
//             buf[len] = '\0'; // Null-terminate the string
//             printf("FD %d: %s\n", fd, buf);
//         } else if (errno != ENOENT) {
//             // Ignore ENOENT (No such file or directory) as it indicates the FD is closed
//             perror("readlink");
//         }
//     }
// }


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
	// if (count_heredoc(token))
	// 	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
		run_cmds(shell, token, pipe_in, pipefd);
	// print_open_fds();
	return (pid);
}
