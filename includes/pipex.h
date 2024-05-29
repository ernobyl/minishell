/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:31:17 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/29 11:09:42 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;
}	t_pipex;

void	handle_error(int exitcode, const char *errormsg);
void	execute(char **argv, char **envp, int *fd);
char	*env_path(char *cmd, char **envp);

void	input_error(void);
int		open_file(char *argv, int i);

#endif