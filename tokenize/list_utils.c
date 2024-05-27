/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:02:45 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/27 13:36:50 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenize.h"

t_struct	*add_new(int token, char *value)
{
	t_struct	*new;

	new = malloc(sizeof(t_struct));
	if (!new)
		return (NULL);
	new->token = token;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_back(t_struct **lst, t_struct *new)
{
	t_struct	*tail;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tail = *lst;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = new;
}

void	add_front(t_list **lst, t_list *new)
{
	if (lst)
		new->next = *lst;
	*lst = new;
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

void	print_nodes(t_struct *stack)
{
	t_struct	*temp;

	temp = stack;
	while (temp)
	{
		printf("type {%d}, value {%s}\n", temp->token, temp->value);
		temp = temp->next;
	}
}

void    push(t_struct **from, t_struct **to)
{
    t_struct    *tmp;

    if (!from || !*from)
        return ;
    tmp = *from;
    *from = (*from)->next;
    tmp->next = *to;
    *to = tmp;
}
void	rotate(t_struct **stack)
{
	t_struct	*first_node;
	t_struct	*last_node;

	if (!stack || !(*stack) || !(*stack)->next)
		return ;
	first_node = *stack;
	*stack = (*stack)->next;
	last_node = (*stack);
	while (last_node->next)
        last_node = last_node->next;
    last_node->next = first_node;
    first_node->next = NULL;
}