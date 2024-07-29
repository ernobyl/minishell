/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:48:05 by emichels          #+#    #+#             */
/*   Updated: 2024/07/29 14:01:27 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/global.h"

void	handle_interrupt(int sig)
{
	(void)sig;
	if (g_signal == 3)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_signal = 0;
	}
	else if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_quit(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_DFL);
	ft_putstr_fd("minishell: quit\n", 1);
	g_signal = 0;
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_interrupt);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
