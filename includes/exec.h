/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:38:14 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/03 11:50:49 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "tokenize.h"
# include <sys/wait.h>

void	exec(t_struct *token, t_env *shell);
void	handle_error(int exitcode, const char *errormsg);
void	execute(char *argv, char **envp);
void	infile_open(int *fd, char *file);
void	outfile_open(int *fd, char *file, int token);
void	open_files(t_struct *token, int *fd);

#endif