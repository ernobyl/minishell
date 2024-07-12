/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:27:21 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/07/12 12:39:48 by kmatjuhi         ###   ########.fr       */
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
	int				index;
	int				type;
	char			*value;
	struct s_struct	*prev;
	struct s_struct	*next;
}					t_struct;

t_struct	*tokenize(char **arr, t_env *shell, int index, int i);

// LIST UTILES
t_struct	*add_new(int token, char *value, int index);
void		add_back(t_struct **lst, t_struct *new);
void		free_stack(t_struct *stack);
t_struct	*is_empty_token(t_struct *token);

#endif