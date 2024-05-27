/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:37:57 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/27 10:16:14 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

char **parse_literals(t_struct *token)
{
	t_struct	*head;
	char		**args;
	int			i;

	i = 0;
	while (token && token->token != PIPE)
	{
		if (token->token == LITERAL)
			args[i++] = ft_strdup(token->value);
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

char **parse_file(t_struct *token)
{
	t_struct	*head;
	char		**args;
	int			i;

	i = 0;
	while (token && token->token != PIPE)
	{
		if (token->token == LITERAL)
			args[i++] = ft_strdup(token->value);
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}
void	exec(t_struct *token, t_env *shell)
{
	int fd[2];
	
	if (pipe(fd) == -1)
	while (token)
	{
		// move all infile to one array
		// move all outfile to an array
		// move all cmds to an array
		// check if cmd matches builtin
		// if yes -> go into builtin
		// else -> go into pipex. and execute
	}
	close(fd[1]);
	close(fd[2]);
	
}
