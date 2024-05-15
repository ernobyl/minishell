/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:53:53 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/15 12:16:07 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

# define TRUE 1
# define FALSE 0

typedef struct s_struct
{
	int				nr;
	char			*token;
	char			*value;
	struct s_struct	*prev;
	struct s_struct	*next;
}					t_struct;

int			parsing(char *input);
char		**split(char const *s);
t_struct	*tokenize(t_struct *token,char **arr);
char		*trim_quote(char *str);
int			validate_syntax(char *input);
char		*ft_strchr_next(const char *s, int c);
char		*find_and_replace(char *str, char *replace, int len);
char		**expand_env(char **arr);

#endif
