/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:02:45 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/06/10 22:27:18 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenize.h"

t_struct	*add_new(int type, char *value, int index)
{
	t_struct	*new;

	new = malloc(sizeof(t_struct));
	if (!new)
		return (NULL);
	new->index = index;
	new->type = type;
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
		printf("index {%d}, type {%d}, value {%s}\n", temp->index, temp->type, temp->value);
		temp = temp->next;
	}
}
