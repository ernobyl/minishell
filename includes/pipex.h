/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:31:17 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/27 10:25:55 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"
# include <sys/wait.h>

char	**parsing_path(char **envp, char *str, int *fd);
void	error_msg(char *str, int *fd, int code);
void	custom_msg(char *cmd, char *str, int *fd, int code);
char	**parsing_args(char *str, int *fd);
char	*ft_sstrjoin(char *s1, char *s2);

#endif