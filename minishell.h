/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:17 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/20 10:24:18 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define EXIT_SIGNAL 100
# define NO_SIGNAL 101

extern char	**environ;

typedef struct s_struct
{
	char			*infile;
	char			*outfile;
	char			*cmd;
	struct s_struct	*prev;
	struct s_struct	*next;
	char			**env;
}					t_struct;

void	heredoc(const char *delimiter);

//int		parsing(char *input);
//char	**split(char const *s);

#endif