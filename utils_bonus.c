/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:40:18 by emichels          #+#    #+#             */
/*   Updated: 2024/05/27 14:50:54 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

// void	handle_error(int exitcode, const char *errormsg)
// {
// 	perror(errormsg);
// 	exit(exitcode);
// }

void	input_error(void)
{
	perror("Error: Invalid argument\n");
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	exit(EXIT_FAILURE);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0664);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0664);
	if (file == -1)
		handle_error(1, "file open error");
	return (file);
}
