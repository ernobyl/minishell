/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:16:30 by emichels          #+#    #+#             */
/*   Updated: 2024/08/02 08:43:28 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/global.h"

static int	prepare_file_and_backup(const char *file, int *stdin_backup)
{
	int	fd;

	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
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

static bool	check_signal(t_env *shell, char *file, int fd)
{
	if (g_signal == 5)
	{
		close(fd);
		unlink(file);
		shell->exit_code = 130;
		return (true);
	}
	return (false);
}

static void	process_lines(int fd, t_env *shell, char **lim, char *file)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (1)
	{
		if (check_signal(shell, file, fd))
			break ;
		line = readline("> ");
		if (!line || is_last_limiter(line, lim, i, shell->k))
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

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin(".tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

void	heredoc(t_env *shell, char **limiter)
{
	int	stdin_backup;
	int	fd;

	set_signal_hd();
	shell->hd_name = generate_heredoc_filename();
	fd = prepare_file_and_backup(shell->hd_name, &stdin_backup);
	if (fd == -1)
		return ;
	process_lines(fd, shell, limiter, shell->hd_name);
	safe_dup2(stdin_backup, 0);
	close(fd);
}
