/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:25:04 by emichels          #+#    #+#             */
/*   Updated: 2024/07/29 15:50:09 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	double_buf_size(char **str, size_t *buf_size)
{
	if (errno == ERANGE)
	{
		*buf_size *= 2;
		free(*str);
		*str = malloc(*buf_size);
		if (*str == NULL)
			return (error_msg("malloc failed", 1));
		return (EXIT_SUCCESS);
	}
	else
	{
		free(*str);
		return (error_msg("pwd: getcwd failed", 1));
	}
}

int	replace_variable(char **env_var, char *new_var)
{
	free((*env_var));
	*env_var = ft_strdup(new_var);
	if ((*env_var) == NULL)
		return (error_msg("strdup failed", 1));
	return (EXIT_SUCCESS);
}

int	add_variable(t_env *shell, char *new_var, int size)
{
	char	**add_env;
	int		i;

	add_env = malloc((size + 2) * sizeof(char *));
	if (add_env == NULL)
		return (error_msg("malloc failed", 1));
	i = 0;
	while (i < size)
	{
		add_env[i] = ft_strdup(shell->env[i]);
		i++;
	}
	add_env[i] = ft_strdup(new_var);
	add_env[i + 1] = NULL;
	ft_free(shell->env);
	shell->env = add_env;
	return (EXIT_SUCCESS);
}

static void	init_sort_struct(int size, t_alpha *sort)
{
	int	i;

	i = 0;
	sort->min_index = -1;
	sort->min_value = NULL;
	sort->printed = (int *)malloc(size * sizeof(int));
	if (sort->printed == NULL)
	{
		printf("malloc failed");
		return ;
	}
	while (i < size)
	{
		sort->printed[i] = 0;
		i++;
	}
}

int	print_list_alpha(char **list, int size)
{
	t_alpha	sort;

	init_sort_struct(size, &sort);
	sort.i = 0;
	while (sort.i < size)
	{
		sort.min_index = -1;
		sort.min_value = NULL;
		sort.k = 0;
		while (sort.k < size)
		{
			if (!sort.printed[sort.k] && (sort.min_index == -1
					|| ft_strcmp(list[sort.k], sort.min_value) < 0))
			{
				sort.min_index = sort.k;
				sort.min_value = list[sort.k];
			}
			sort.k++;
		}
		printf("declare -x %s\n", list[sort.min_index]);
		sort.printed[sort.min_index] = 1;
		sort.i++;
	}
	free(sort.printed);
	return (EXIT_SUCCESS);
}
