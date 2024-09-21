/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:48:46 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/22 15:17:13 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (s1 == 0)
		return (NULL);
	if (set == 0)
		return (ft_strdup(s1));
	i = 0;
	while (ft_isset(s1[i], set) == 1)
		i++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	j = ft_strlen(s1);
	while (ft_isset(s1[j - 1], set) == 1)
		j--;
	return (ft_substr(s1, i, (j - i)));
}
