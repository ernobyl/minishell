/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:38:14 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/06 21:46:57 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define HEREDOC 42
# define INFILE 43
# define OUTFILE 44
# define D_OUTFILE 45
# define LITERAL 46
# define PIPE 47

# include "minishell.h"
# include "tokenize.h"

void	exec(t_struct *token, t_env *shell);
void	handle_error(int exitcode, const char *errormsg);
void	execute(char *cmd, char **args, char **envp);
void	infile_open(int *fd, char *file);
void	outfile_open(int *fd, char *file, int token);
void	open_files(t_struct *token, int *fd);

#endif