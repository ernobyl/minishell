/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 03:44:47 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/06 13:26:00 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/global.h"

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 5;
		write(1, "\n", 1);
		close(0);
	}
}

void	set_signal_hd(void)
{
	signal(SIGINT, signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

bool	set_fork_signal(void)
{
	if (g_signal == 5)
		return (false);
	g_signal = 3;
	signal(SIGQUIT, handle_quit);
	return (true);
}
