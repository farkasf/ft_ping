/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 00:30:05 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/24 18:26:35 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	i = 0;
	while (!(dst == NULL && size == 0) && dst[i] && i < size)
		i++;
	j = 0;
	while (!(src == NULL && size == 0) && src[j])
		j++;
	if (size < i)
		temp = j + size;
	else
		temp = j + i;
	j = 0;
	while (size != 0 && src[j] && (i + 1 < size))
		dst[i++] = src[j++];
	if (size > i)
		dst[i] = '\0';
	return (temp);
}
