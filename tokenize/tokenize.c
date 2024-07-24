/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:20:45 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/24 13:34:31 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenize.h"

static int	match_tokentype(char *str)
{
	int	type;

	type = LITERAL;
	if (ft_strcmp("<<", str) == 0)
		type = HEREDOC;
	else if (ft_strcmp("<", str) == 0)
		type = INFILE;
	else if (ft_strcmp(">>", str) == 0)
		type = D_OUTFILE;
	else if (ft_strcmp(">", str) == 0)
		type = OUTFILE;
	else if (ft_strcmp("|", str) == 0)
		type = PIPE;
	return (type);
}

t_struct	*tokenize(char **arr, t_env *shell, int index, int i)
{
	t_struct	*head;
	int			type;

	head = NULL;
	while (arr[i])
	{
		type = match_tokentype(arr[i]);
		if (type == PIPE)
		{
			if (i > 0 && (ft_strcmp("|", arr[i - 1]) == 0))
				type = LITERAL;
			else
				index++;
		}
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
