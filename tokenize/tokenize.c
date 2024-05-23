/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:20:45 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/23 11:38:22 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenize.h"

char	*find_tokentype(char *str)
{
	if (ft_strncmp("<<", str, 2) == 0)
		return ("HEREDOC");
	if (ft_strncmp("<", str, 1) == 0)
		return ("INFILE");
	if (ft_strncmp(">>", str, 2) == 0)
		return ("D_OUTFILE");
	if (ft_strncmp(">", str, 1) == 0)
		return ("OUTFILE");
	return (NULL);
}

t_struct *token(char **arr)
{
	t_struct	*head;
	t_struct	*new;
	int			i;
	int			pipe;
	int			cmd;
	char		*token;

	head = NULL;
	i = 0;
	cmd = 0;
	pipe = 0;
	while (arr[i])
	{
		token = find_tokentype(arr[i]);
		if (token)
		{
			new = add_new(token, arr[i + 1], pipe);
			i++;
		}
		else if (arr[i][0] == '|')
		{
			pipe++;
			cmd = 0;
		}
		else
		{
			if (cmd == 0)
			{
				new = add_new("CMD", arr[i], pipe);
				cmd = 1;
			}
			else
				new = add_new("LIT", arr[i], pipe);
		}
		i++;
		add_back(&head, new);
	}
	return (head);
}

t_struct	*tokenize(char **arr)
{
	t_struct *t;
	int		ret_value;
	
	t = token(arr);
	print_nodes(t);
	ret_value = run_builtin(input, &shell);
	if (ret_value != 0)
	{
		printf("FAILURE");
		exit(1);
	}
	return (t);
}