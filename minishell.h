/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:17 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/29 12:51:08 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>

typedef struct s_struct
{
	char			*infile;
	char			*outfile;
	char			*cmd;
	char			*option;
	char			*arg;
	struct s_struct	*prev;
	struct s_struct	*next;
}					t_struct;

int		parsing(char *input, sig_atomic_t flag);
char	**split(char const *s);
char	*skip_set(char *str, char *set);
int		pwd_builtin(void);
int		cd_builtin(const char *path);
int		echo_builtin(char *file, char *input);
int		export_builtin(char ***environ, char *new_var);
int		unset_builtin(char ***environ, char *to_unset);
int		env_builtin(char **environ);
int		built_ins(char *input, char *param, sig_atomic_t flag);

#endif