/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:20:45 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/24 19:20:36 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenize.h"

static int	match_tokentype(char *str)
{
	if (ft_strcmp("<<", str) == 0)
		return (HEREDOC);
	else if (ft_strcmp("<", str) == 0)
		return (INFILE);
	else if (ft_strcmp(">>", str) == 0)
		return (D_OUTFILE);
	else if (ft_strcmp(">", str) == 0)
		return (OUTFILE);
	else if (ft_strcmp("|", str) == 0)
		return (PIPE);
	return (LITERAL);
}

t_struct	*tokenize(char **arr)
{
	t_struct	*head;
	t_struct	*new;
	int			i;
	int			token;

	head = NULL;
	i = 0;
	while (arr[i])
	{
		token = match_tokentype(arr[i]);
		if (token == PIPE || token == LITERAL)
			new = add_new(token, arr[i]);
		else
		{
			new = add_new(token, arr[i + 1]);
			i++;
		}
		i++;
		add_back(&head, new);
	}
	return (head);
}

	// ret_value = run_builtin(cmd, param, shell);
	// if (ret_value != 0)
	// {
	// 	printf("FAILURE");
	// 	exit(1);
