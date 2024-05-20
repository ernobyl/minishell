/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:53:53 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/20 13:25:51 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# include <stdbool.h>

typedef struct s_struct
{
	int				nr;
	char			*token;
	char			*value;
	struct s_struct	*prev;
	struct s_struct	*next;
}					t_struct;

bool		parsing(char *input);
char		*validate_syntax(char *str);
bool		ft_isquote(char c);
bool		matching_quote(char *str, int i, char quote);
int			skip_quotes(char *str, int i, char quote);
bool 		ft_isspecialchar(char c);
bool 		ft_iswhitespace(char c);
char		**split(char *s);
t_struct	*tokenize(t_struct *token,char **arr);
char		*trim_quote(char *str);
char		*ft_strchr_next(const char *s, int c);
char		*find_and_replace(char *str, char *replace, int len);
char		**expand_env(char **arr);
char		*mod_str(char *str);

#endif
