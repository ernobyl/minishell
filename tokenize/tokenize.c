/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:20:45 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/08 11:46:30 by kmatjuhi         ###   ########.fr       */
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

t_struct	*tokenize(char **arr, t_env *shell)
{
	t_struct	*head;
	int			index;
	int			i;
	int			type;

	head = NULL;
	i = 0;
	index = 0;
	while (arr[i])
	{
		type = match_tokentype(arr[i]);
		if (type == PIPE)
			index++;
		if (type == PIPE || type == LITERAL)
			add_back(&head, add_new(type, arr[i], index));
		else
		{
			add_back(&head, add_new(type, arr[i + 1], index));
			i++;
		}
		i++;
	}
	shell->cmds_num = index;
	return (head);
}
