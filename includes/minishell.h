/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:17 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/07 19:10:33 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "tokenize.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>

# define EXIT_MAIN 50

extern char				**environ;
typedef struct s_struct	t_struct;

typedef struct s_env
{
	t_struct	*token;
	char		**env;
	char		**args;
	int			*pids;
	char		*hd_name;
	char		*infile;
	char		*outfile;
	char		*prev_dir;
	char		*home;
	int			exit_code;
	int			cmds_num;
	int			found;
	int			i;
	int			k;
	bool		is_empty;
}				t_env;

// SIGNALS
void	handle_quit(int sig);
void	setup_signal_handlers(void);
void	reset_signal_handlers(void);
bool	set_fork_signal(void);
void	set_signal_hd(void);

#endif