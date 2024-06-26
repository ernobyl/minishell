/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:48:03 by emichels          #+#    #+#             */
/*   Updated: 2024/06/26 22:39:58 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define EXIT_SIGNAL 100
# define NO_SIGNAL 101

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

typedef struct s_alphasort
{
	int		i;
	int		k;
	char	*min_value;
	int		*printed;
	int		min_index;
}			t_alpha;

int		error_msg(char *msg, int code);
char	*skip_set(char *str, char *set);
char	**init_env_list(void);
int		print_list_alpha(char **list, int size);
int		replace_variable(char **env_var, char *new_var);
int		add_variable(t_env *shell, char *new_var, int size);
int		double_buf_size(char **str, size_t *buf_size);
int		pwd_builtin(void);
int		cd_builtin(const char *path);
int		echo_builtin(char *file, char **param);
int		export_builtin(int ret_value, t_env *shell, char *new_var);
int		export_array(int ret_value, t_env *shell, char **array);
int		unset_builtin(t_env *shell, char *to_unset);
int		env_builtin(t_env *shell);
int		run_builtin(char *cmd, char **param, t_env *shell);
void	exit_builtin(char **param, t_env *shell);
void	export_shlvl(char **envp);

#endif