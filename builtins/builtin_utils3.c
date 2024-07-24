/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:31:47 by emichels          #+#    #+#             */
/*   Updated: 2024/07/24 14:46:40 by emichels         ###   ########.fr       */
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
