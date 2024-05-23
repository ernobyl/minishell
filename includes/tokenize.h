/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:27:21 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/23 11:34:54 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "builtins.h"
# include "minishell.h"

typedef struct s_struct
{
	int				nr;
	char			*token;
	char			*value;
	struct s_struct	*prev;
	struct s_struct	*next;
}					t_struct;

t_struct	*tokenize(char **arr);
t_struct	*add_new(char *token, char *value, int i);
void		add_front(t_struct **lst, t_struct *new);
void		add_back(t_struct **lst, t_struct *new);
void		free_stack(t_struct **stack);
void		print_nodes(t_struct *stack);
int			count_nodes(t_struct *stack);

#endif