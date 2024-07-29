/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:48:03 by emichels          #+#    #+#             */
/*   Updated: 2024/07/29 12:35:33 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "tokenize.h"
# include "minishell.h"

# define EXIT_SIGNAL 100
# define NO_SIGNAL 101

typedef struct s_struct	t_struct;

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
int		cd_builtin(t_env *shell, const char *path);
int		echo_builtin(char *file, char **param);
int		export_builtin(t_env *shell, char *new_var);
int		export_array(int r_val, t_env *shell, char **ar);
int		unset_builtin(t_env *shell, char *to_unset);
int		env_builtin(t_env *shell);
int		exit_builtin(char **param, t_env *shell, t_struct *token);
void	export_shlvl(char **envp);
int		check_export(char *new_var, int i);
int		get_builtin_num(char *input);
void	env_replace_var(t_env *shell, char *new_var);
char	*current_dir(void);
char	*custom_getenv(t_env *shell, char *var);
int		handle_oldpwd(t_env *shell, char *prev_dir);
void	update_pwd(t_env *shell);

#endif