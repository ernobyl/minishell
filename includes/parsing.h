/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:53:53 by kmatjuhi          #+#    #+#             */
/*   Updated: 2024/08/06 20:51:08 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "tokenize.h"
# include <stdbool.h>
# include "exec.h"

char	**split(char *s);
char	*add_space(char *str);
char	*validate_syntax(t_env *shell, char *str);
bool	parsing(char *input, t_env *shell);

// EXPAND
char	**expand_env(char **arr, t_env *shell);
bool	expanded_all(char *str, t_env *shell);
char	*find_and_replace_env(char *str, char *replace, int len);
char	*find_variable(char *str);
char	*expand_str(char *str, t_env *shell);
int		find_env_var(t_env *shell, char *var);

// PARSING UTILS
char	*ft_strchr_next(const char *s, int c);
bool	ft_isspecialchar(char c);
bool	ft_iswhitespace(char c);
char	*new_str(char *str);

// QUOTE FUNC
char	*trim_quote(char *str);
int		skip_quotes(char *str, int i, char quote);
bool	matching_quote(char *str, int i, char quote);
bool	ft_isquote(char c);

#endif
