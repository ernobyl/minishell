/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:53:53 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/23 12:10:12 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "tokenize.h"
# include <stdbool.h>

bool	parsing(char *input, t_env *shell);
bool	ft_isquote(char c);
bool	matching_quote(char *str, int i, char quote);
bool	ft_isspecialchar(char c);
bool	ft_iswhitespace(char c);
char	*validate_syntax(char *str);
char	*trim_quote(char *str);
char	*ft_strchr_next(const char *s, int c);
char	*find_and_replace(char *str, char *replace, int len);
char	*mod_str(char *str);
char	**split(char *s);
char	**expand_env(char **arr);
int		skip_quotes(char *str, int i, char quote);

#endif
