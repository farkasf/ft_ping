/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:18:50 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/14 04:00:55 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		((unsigned char *)dst)[i] = c;
		i++;
	}
	return (dst);
}
