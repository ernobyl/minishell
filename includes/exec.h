/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:38:14 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/08 12:42:14 by kmatjuhi         ###   ########.fr       */
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

# include <sys/wait.h>
# include "minishell.h"
# include "tokenize.h"
# include <stdbool.h>

int		child(t_env *shell, t_struct *token, int *pipe_in, int *pipefd);
void	exec_cmds(t_struct *token, t_env *shell);
void	execute(char *cmd, char **args, char **envp);
int		run_builtin(char *cmd, char **param, t_env *shell, t_struct *token);
// char	**args_list(t_struct *token);

// ERROR
void	handle_error(int exitcode, const char *errormsg);
void	handle_error_exec(int exitcode, char *cmd, char *msg);

// // FILES FUNCTIONS
void	open_files(t_struct *token);
void	save_fds(int *fd);
void	restore_fds(int *fd, int *pipefd, int *pipe_in);
void	close_fds(int *fd, int pipe_in);
void	heredoc(char *limiter);

// // SAFE FUNCTIONS
void	safe_pipe(int *fd);
void	safe_close(int fd);
int		safe_fork(void);
void	safe_dup2(int fd, int fd2);

#endif