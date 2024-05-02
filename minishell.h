/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:17 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/02 15:12:37 by emichels         ###   ########.fr       */
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
}					t_struct;

typedef enum e_builtin_n
{
	EXIT,
	PWD,
	CD,
	ECHO,
	EXPORT,
	UNSET,
	ENV,
	NOT_BUILTIN
}	t_bnum;

//int		parsing(char *input);
//char	**split(char const *s);

int		error_msg(char *msg);

int		replace_variable(char **env_var, char *new_var);
int		add_variable(char ***env, char *new_var, int size);

char	*skip_set(char *str, char *set);
int		double_buf_size(char **str, size_t *buf_size);
int		pwd_builtin(void);
int		cd_builtin(const char *path);
int		echo_builtin(char *file, char *input);
int		export_builtin(char ***env, char *new_var);
int		unset_builtin(char ***env, char *to_unset);
int		env_builtin(char **env);
int		run_builtin(char *input);

#endif