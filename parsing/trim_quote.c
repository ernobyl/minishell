/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:15:37 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/23 10:34:14 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(char *input)
{
	int		i;
	char	sign;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && ((input[i + 1] == '|') || input[i + 1] == '\0'))
			return (0);
		if (input[i] == '"' || input[i] == '\'')
		{
			sign = input[i++];
			while (input[i] && input[i] != sign)
				i++;
			if (input[i] != sign)
				return (0);
		}
		if (input[i] == '<' && ((input[i + 1] == '<' && input[i + 2] == '<') \
		|| input[i + 1] == '\0'))
			return (0);
		if (input[i] == '>' && ((input[i + 1] == '>' && input[i + 2] == '>') \
		|| input[i + 1] == '\0'))
			return (0);
		i++;
	}
	return (1);
}

int	count_trim_letters(char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				i++;
				j++;
			}
			i++;
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*trim_quote(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (count_trim_letters(str) + 1));
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				new_str[j++] = str[i++];
			i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

int	parsing(char *input, sig_atomic_t flag)
{
	t_struct	*cmd;
	int			i;
	char		**arr;

	i = 0;
	input = ft_strtrim(input, " ");
	if (!check_syntax(input))
	{
		printf("Syntax error\n");
		free(input);
		return (0);
	}
	arr = split(input);
	free(input);
	if (!arr)
		return (0);
	while (arr[i])
	{
		arr[i] = trim_quote(arr[i]);
		// if (built_ins(arr[0], arr[1], flag) == 0)
		// {
		// 	printf("SUCCESS\n");
		// 	break ;
		// }
		// else
		printf("%s\n", arr[i]);
		i++;
	}
	ft_free(arr);
	return (1);
}
