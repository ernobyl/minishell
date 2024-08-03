/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:47:48 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/02 09:57:40 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	handle_error(int exitcode, const char *errormsg)
{
	perror(errormsg);
	exit(exitcode);
}

void	handle_error_exec(int exitcode, t_env *shell, char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	ft_free(shell->args);
	ft_free(shell->env);
	free(shell->pids);
	exit(exitcode);
}

int	error_msg_fd(char *str, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	return (code);
}

void	free_error_fd(t_env *shell)
{
	free_stack(shell->token);
	ft_free(shell->env);
	ft_free(shell->args);
	free(shell->pids);
	exit(1);
}

void	error_msg_hd(t_env *shell, char *str, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	free_stack(shell->token);
	ft_free(shell->env);
	ft_free(shell->args);
	free(shell->pids);
	exit(code);
}
