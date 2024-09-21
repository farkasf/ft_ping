/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:02:56 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/24 17:08:41 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (s == 0)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		return ((char *) ft_calloc(1, sizeof(char)));
	if (ft_strlen(s) <= start + len)
		str = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	else
		str = malloc((len + 1) * sizeof(char));
	if (str == 0)
		return (NULL);
	while (s[start] && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
