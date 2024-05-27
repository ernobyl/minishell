/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:27:21 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/27 10:58:11 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "builtins.h"
# include "minishell.h"

# define HEREDOC 42
# define INFILE 43
# define OUTFILE 44
# define D_OUTFILE 45
# define LITERAL 46
# define PIPE 47

typedef struct s_struct
{
	int				token;
	char			*value;
	struct s_struct	*prev;
	struct s_struct	*next;
}					t_struct;

t_struct	*tokenize(char **arr);
t_struct	*add_new(int token, char *value);
void		add_front(t_struct **lst, t_struct *new);
void		add_back(t_struct **lst, t_struct *new);
void		free_stack(t_struct **stack);
void		print_nodes(t_struct *stack);
int			count_nodes(t_struct *stack);

#endif