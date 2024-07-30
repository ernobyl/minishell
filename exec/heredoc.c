/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:16:30 by emichels          #+#    #+#             */
/*   Updated: 2024/07/29 15:30:08 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/global.h"

static void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		//printf("going into singla");
		g_signal = 5;
		write(1, "\n", 1);
		close(0);
	}
}

// static void	parent_wait(int *fd, pid_t reader)
// {
// 	int	status;

// 	close(fd[1]);
// 	waitpid(reader, &status, 0);
// 	if (g_signal == 5
// 		|| ((status) && WEXITSTATUS(status) == 130))
// 	{
// 		close(fd[0]);
// 		exit(130);
// 	}
// 	else
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 	}
// }

// static void	sig_exit_heredoc(int *fd)
// {
// 	close(fd[1]);
// 	exit(130);
// }

// static void	heredoc_child(t_env *shell, int *fd, char *line, char **limiter)
// {
// 	int	i;

// 	i = 0;
// 	close(fd[0]);
// 	while (!g_signal)
// 	{
// 		line = read_line();
// 		if (g_signal == 5)
// 			sig_exit_heredoc(fd);
// 		if (is_last_limiter(line, limiter, i, shell->k))
// 			break ;
// 		if (is_limiter(line, limiter, &i))
// 			continue ;
// 		if (i == shell->k - 1)
// 		{
// 			line = handle_expansion(line, shell);
// 			if (!line)
// 				exit(1);
// 			write_line_to_fd(fd[1], line);
// 		}
// 		free(line);
// 	}
// 	close(fd[1]);
// 	exit(0);
// }


static void	heredoc_child(char *file_name, t_env *shell, char *line, char **limiter)
{
	int	i;
	int fd;
	i = 0;
	int stdin_backup;

	stdin_backup = dup(0);
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (g_signal == 5)
		{
			close(fd);
			// printf("1\n");	
			// fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
			// printf("2\n");	
			// write_line_to_fd(fd, "\0");
			// printf("3\n");
			shell->exit_code = 130;
			break ;
		}
		if (line == NULL)
			break ;
		if (is_last_limiter(line, limiter, i, shell->k))
			break ;
		if (is_limiter(line, limiter, &i))
			continue ;
		if (i == shell->k - 1)
		{
			line = handle_expansion(line, shell);
			if (!line)
				break ;
			write_line_to_fd(fd, line);
		}
		free(line);
	}
	safe_dup2(stdin_backup, 0);
	close(fd);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("temp/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

// void	heredoc(t_env *shell, char **limiter)
// {
// 	pid_t	reader;
// 	int		fd[2];
// 	char	*line;

// 	printf("inside the heredoc\n");
// 	g_signal = 0;
// 	line = NULL;
// 	if (pipe(fd) == -1)
// 	{
// 		perror("pipe failed");
// 		return ;
// 	}
// 	reader = fork();
// 	if (reader == -1)
// 	{
// 		perror("fork failed");
// 		return ;
// 	}
// 	if (reader == 0)
// 	{
// 		g_signal = 0;
// 		line = NULL;
// 		shell->hd_name = generate_heredoc_filename();
// 		heredoc_child(shell->hd_name, shell, line, limiter);
// 		ft_free(limiter);
// 		exit(EXIT_SUCCESS);
// 	}

// }
void heredoc(t_env *shell, char **limiter)
{
	char	*line;
	char	*file_name;
	int		file1;

	signal(SIGINT, signal_heredoc);
	g_signal = 0;
	line = NULL;
	shell->hd_name = generate_heredoc_filename();
	heredoc_child(shell->hd_name, shell, line, limiter);
}