/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:15:37 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/04/26 09:43:38 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && ((input[i + 1] == '|') || input[i + 1] == '\0'))
			return (0);
		if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] != quote)
				return (0);
		}
		i++;
	}
	return (1);
}

int	parsing(char *input)
{
	t_struct	*cmd;
	t_struct	*file;
	int			i;
	char		**arr;

	i = 0;
	input = ft_strtrim(input, " ");
	if (!check_syntax(input))
	{
		printf("Syntax error\n");
		return (0);
	}
	arr = split(input);
	if (!arr)
		return (0);
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	printf("%s", arr[i]);
	return (1);
}
