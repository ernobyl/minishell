/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:38:14 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/06 12:09:10 by kmatjuhi         ###   ########.fr       */
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
# include "parsing.h"
# include "global.h"

int		child(t_env *shell, t_struct *token, int *pipe_in, int *pipefd);
void	exec_cmds(t_struct *token, t_env *shell);
void	execute(t_env *shell, char *cmd, char **args, char **envp);
int		run_builtin(char *cmd, char **param, t_env *shell, t_struct *token);
char	**args_list(t_struct *token);
char	*env_path(char *cmd, char **envp);

// ERROR
void	handle_error(int exitcode, const char *errormsg);
void	handle_error_exec(int exitcode, t_env *shell, char *cmd, char *msg);
int		error_msg_fd(char *str, int code);
void	free_error_fd(t_env *shell);
void	error_msg_hd(t_env *shell, char *str, int code);

// FILES FUNCTIONS
int		open_files(t_env *shell, t_struct *token);
char	*infile_open(char *file);
void	save_fds(int *fd);
void	restore_fds(int *fd, int *pipefd, int *pipe_in, int cmds);
void	close_fds(int *fd, int pipe_in);

// HEREDOC
int		count_heredoc(t_struct *token);
void	heredoc(t_env *shell, char **limiter);
bool	is_last_limiter(char *line, char **limiter, int i, int k);
bool	is_limiter(char *line, char **limiter, int *i);
char	*handle_expansion(char *line, t_env *shell);
void	write_line_to_fd(int fd, char *line);
void	heredoc_open(t_env *shell, t_struct *token);

// SAFE FUNCTIONS
void	safe_pipe(int *fd);
void	safe_close(int fd);
int		safe_fork(void);
void	safe_dup2(int fd, int fd2);

#endif