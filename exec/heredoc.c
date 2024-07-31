/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:16:30 by emichels          #+#    #+#             */
/*   Updated: 2024/07/31 04:07:49 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/global.h"

static void	hd_child(char *file, t_env *shell, char *line, char **lim)
{
	int	stdin_backup;
	int	fd;
	int	i;

	i = 0;
	stdin_backup = dup(0);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (g_signal == 5)
		{
			close(fd);
			shell->exit_code = 130;
			break ;
		}
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

void	heredoc(t_env *shell, char **limiter)
{
	char	*line;

	set_signal_hd();
	line = NULL;
	shell->hd_name = generate_heredoc_filename();
	hd_child(shell->hd_name, shell, line, limiter);
}
