/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:18:13 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/24 01:30:30 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	out;

	i = 0;
	out = 0;
	while (src[out])
		out++;
	if (size > 0)
	{
		while (src[i] && (i + 1 < size))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (out);
}
