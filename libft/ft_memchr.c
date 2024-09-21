/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 02:45:51 by ffarkas           #+#    #+#             */
/*   Updated: 2023/04/25 21:44:44 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int ch, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		if (((unsigned char *)buf)[i] == (unsigned char)ch)
			return ((void *)&((char *)buf)[i]);
		i++;
	}
	return (NULL);
}
