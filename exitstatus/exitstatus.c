/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitstatus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:52:53 by emichels          #+#    #+#             */
/*   Updated: 2024/06/17 14:23:41 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	exit_st(int status)
{
	g_exit_status = status;
	exit(g_exit_status);
}