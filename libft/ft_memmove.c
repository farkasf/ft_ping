/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:40:12 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/14 04:00:08 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t length)
{
	size_t	i;

	if (dst > src)
	{
		i = length;
		while (i > 0)
		{
			i--;
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
	}
	else
		ft_memcpy(dst, src, length);
	return (dst);
}
