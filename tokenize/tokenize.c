/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:20:45 by kmatjuhi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/29 09:50:58 by kmatjuhi         ###   ########.fr       */
=======
/*   Updated: 2024/06/03 12:04:10 by kmatjuhi         ###   ########.fr       */
>>>>>>> 2c01816ec056bcfa8f40265a1dd94ce19b3367ff
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
	int			index;
	int			i;
	int			token;

	head = NULL;
	i = 0;
	index = 0;
	while (arr[i])
	{
		token = match_tokentype(arr[i]);
		if (token == PIPE)
			index++;
		if (token == PIPE || token == LITERAL)
			new = add_new(token, arr[i], index);
		else
		{
			new = add_new(token, arr[i + 1], index);
			i++;
		}
		i++;
		add_back(&head, new);
	}
	return (head);
}
