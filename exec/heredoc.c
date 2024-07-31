/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:16:30 by emichels          #+#    #+#             */
/*   Updated: 2024/07/31 03:00:26 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/global.h"

static void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 5;
		write(1, "\n", 1);
		close(0);
	}
}

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

void heredoc(t_env *shell, char **limiter)
{
	char	*line;

	signal(SIGINT, signal_heredoc);
	g_signal = 0;
	line = NULL;
	shell->hd_name = generate_heredoc_filename();
	heredoc_child(shell->hd_name, shell, line, limiter);
}
