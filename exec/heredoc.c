/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:16:30 by emichels          #+#    #+#             */
/*   Updated: 2024/08/06 22:31:03 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/global.h"

static int	prepare_file_and_backup(const char *file, int *stdin_backup)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		return (-1);
	*stdin_backup = dup(0);
	if (*stdin_backup == -1)
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

static void	process_lines(int fd, t_env *shell, char **lim)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_last_limiter(line, lim, i, shell->k))
			break ;
		if (is_limiter(line, lim, &i))
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
}

void	heredoc(t_env *shell, char **limiter)
{
	int	stdin_backup;
	int	fd;

	set_signal_hd();
	shell->hd_name = ".tmp_heredoc_file";
	fd = prepare_file_and_backup(shell->hd_name, &stdin_backup);
	if (fd == -1)
		return ;
	process_lines(fd, shell, limiter);
	ft_free(limiter);
	safe_dup2(stdin_backup, 0);
	close(fd);
}
