/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:02:45 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/20 22:19:28 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenize.h"

t_struct	*add_new(char *token, char *value, int i)
{
	t_struct	*new;

	new = malloc(sizeof(t_struct));
	if (!new)
		return (NULL);
	new->nr = i;
	new->token = token;
	new->value = value;
	new->next = new;
	new->prev = new;
	return (new);
}

void	add_front(t_struct **lst, t_struct *new)
{
	t_struct	*head;
	t_struct	*tail;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	head = *lst;
	tail = (*lst)->prev;
	new->next = head;
	new->prev = tail;
	tail->next = new;
	head->prev = new;
	*lst = new;
}

void	add_back(t_struct **lst, t_struct *new)
{
	t_struct	*head;
	t_struct	*tail;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	head = *lst;
	tail = (*lst)->prev;
	new->next = head;
	new->prev = tail;
	tail->next = new;
	head->prev = new;
}

void	free_stack(t_struct **stack)
{
	t_struct	*temp;
	t_struct	*next;

	if (*stack)
	{
		temp = (*stack)->next;
		while (temp != *stack)
		{
			next = temp->next;
			free(temp);
			temp = next;
		}
		free(*stack);
	}
}

int	count_nodes(t_struct *stack)
{
	t_struct	*temp;
	int			count;

	count = 1;
	temp = stack;
	stack = stack->next;
	while (temp != stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

void	print_nodes(t_struct *stack)
{
	t_struct	*temp;

	temp = stack;
	printf("nr {%d}, type {%s}, value {%s}\n", stack->nr, stack->token, stack->value);
	stack = stack->next;
	while (temp != stack)
	{
		printf("nr {%d}, type {%s}, value {%s}\n", stack->nr, stack->token, stack->value);
		stack = stack->next;
	}
}
