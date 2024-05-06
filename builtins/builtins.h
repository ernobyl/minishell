/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:48:03 by emichels          #+#    #+#             */
/*   Updated: 2024/05/06 15:02:54 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include "../libft/libft.h"

extern char	**environ;

typedef struct s_builtins
{
	char	**env;
}			t_builtins;

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

int		error_msg(char *msg);

char	**init_env_list(void);

int		replace_variable(char **env_var, char *new_var);
int		add_variable(char **env, char *new_var, int size);

char	*skip_set(char *str, char *set);
int		double_buf_size(char **str, size_t *buf_size);
int		pwd_builtin(void);
int		cd_builtin(const char *path);
int		echo_builtin(char *file, char *input);
int		export_builtin(char **env, char *new_var);
int		unset_builtin(char **env, char *to_unset);
int		env_builtin(char **env);
int		run_builtin(char *input, char **env);

#endif