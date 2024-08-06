/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:31:47 by emichels          #+#    #+#             */
/*   Updated: 2024/08/06 14:44:44 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	update_pwd(t_env *shell)
{
	char	*pwd;
	char	*cur_path;

	cur_path = current_dir();
	pwd = ft_strjoin("PWD=", cur_path);
	env_replace_var(shell, pwd);
	free(pwd);
	free(cur_path);
}

void	change_oldpwd(t_env *shell)
{
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", shell->prev_dir);
	env_replace_var(shell, old_pwd);
	free(old_pwd);
}
