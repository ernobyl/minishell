/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:38:14 by kmatjuhi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/29 11:17:25 by kmatjuhi         ###   ########.fr       */
=======
/*   Updated: 2024/06/03 11:50:49 by kmatjuhi         ###   ########.fr       */
>>>>>>> 2c01816ec056bcfa8f40265a1dd94ce19b3367ff
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
<<<<<<< HEAD
# include "pipex.h"

void	exec(t_struct *token, t_env *shell);
void	infile_open(int *fd, char *file);
void	outfile_open(int *fd, char *file, int token);
void	xcute_cmd(char *cmd, char **envp, int *fd);
void	error_msg_kim(char *str, int *fd, int code);
=======
# include <sys/wait.h>

void	exec(t_struct *token, t_env *shell);
void	handle_error(int exitcode, const char *errormsg);
void	execute(char *argv, char **envp);
void	infile_open(int *fd, char *file);
void	outfile_open(int *fd, char *file, int token);
void	open_files(t_struct *token, int *fd);
>>>>>>> 2c01816ec056bcfa8f40265a1dd94ce19b3367ff

#endif