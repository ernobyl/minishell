/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:38:14 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/12 16:07:59 by emichels         ###   ########.fr       */
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

void	exec(t_struct *token, t_env *shell);
void	handle_error(int exitcode, const char *errormsg);
void	execute(char *cmd, char **args, char **envp);
void	open_files(t_struct *token);
void	save_fds(int *fd);
void	restore_fds(int *fd);
void	close_fds(int *fd, int old_pipe_in);

#endif