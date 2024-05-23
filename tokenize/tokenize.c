/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:20:45 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/23 12:51:26 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenize.h"

static int find_tokentype(char *str)
{
	if (ft_strncmp("<<", str, 2) == 0)
		return (HEREDOC);
	if (ft_strncmp("<", str, 1) == 0)
		return (INFILE);
	if (ft_strncmp(">>", str, 2) == 0)
		return (D_OUTFILE);
	if (ft_strncmp(">", str, 1) == 0)
		return (OUTFILE);
	return (0);
}

t_struct *token(char **arr)
{
	t_struct	*head;
	t_struct	*new;
	int			i;
	int			pipe;
	int			cmd;
	int			token;

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
				new = add_new(CMD, arr[i], pipe);
				cmd = 1;
			}
			else
			{
				if (arr[i][0] == '-')
					new = add_new(OPTION, arr[i], pipe);
				else
					new = add_new(LIT, arr[i], pipe);
			}
		}
		i++;
		add_back(&head, new);
	}
	return (head);
}
char *find_cmd(t_struct *stack)
{
	t_struct *temp;

	temp = stack;
	if (stack->token != CMD)
		temp = temp->next;
	while (temp != stack && temp->token != CMD)
		temp = temp->next;
	if (temp->token != CMD)
		return (NULL);
	return (temp->value);
}

char *find_param(t_struct *stack)
{
	t_struct *temp;

	if (stack->token != LIT)
		temp = temp->next;
	while (temp != stack && temp->token != LIT)
		temp = temp->next;
	if (temp->token != LIT)
		return (NULL);
	return (temp->value);
}

t_struct	*tokenize(char **arr, t_env *shell)
{
	t_struct	*t;
	char *cmd;
	char *param;
	int ret_value;

	t = token(arr);
	print_nodes(t);
	cmd = find_cmd(t);
	param = find_param(t);
	ret_value = run_builtin(cmd, param, shell);
	if (ret_value != 0)
	{
		printf("FAILURE");
		exit(1);
	}
	return (t);
}