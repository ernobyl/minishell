/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:13:06 by emichels          #+#    #+#             */
/*   Updated: 2023/11/15 11:52:28 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		i2;
	char		*result;

	i = start;
	if (!*s || start > ft_strlen(s))
		return (ft_strdup(""));
	else
	{
		if (ft_strlen(s) - i < len)
			result = malloc(sizeof(char) * ft_strlen(s) - i + 1);
		else
			result = malloc(sizeof(char) * len + 1);
	}
	if (!result)
		return (NULL);
	i2 = 0;
	while (i2 < len && s[i])
	{
		result[i2] = (char)s[i];
		i++;
		i2++;
	}
	result[i2] = '\0';
	return (result);
}
