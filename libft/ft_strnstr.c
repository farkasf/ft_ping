/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 03:31:39 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/23 16:56:56 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == 0)
		return (((char *)big));
	if (len == 0)
		return (NULL);
	i = 0;
	while (big[i] && len > i && len > 0)
	{
		j = 0;
		while (little[j] && (big[i + j] == little[j]) && (j < len - i))
			j++;
		if (little[j] == 0)
			return ((char *) &big[i]);
		i++;
	}
	return (NULL);
}
