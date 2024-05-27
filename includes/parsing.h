/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:53:53 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/05/25 01:26:41 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "tokenize.h"
# include <stdbool.h>
# include "exec.h"

bool	ft_isquote(char c);
bool	ft_isspecialchar(char c);
bool	ft_iswhitespace(char c);
bool	matching_quote(char *str, int i, char quote);
bool	parsing(char *input, t_env *shell);
char	**expand_env(char **arr, t_env *shell);
char	*find_and_replace(char *str, char *replace, int len);
char	*ft_strchr_next(const char *s, int c);
char	*mod_str(char *str);
char	**split(char *s);
char	*trim_quote(char *str);
char	*validate_syntax(char *str);
int		skip_quotes(char *str, int i, char quote);

#endif
