/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 04:21:21 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/22 15:21:02 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	int		i;
	int		src_l;

	i = 0;
	src_l = ft_strlen(src);
	dst = (char *)malloc((src_l + 1) * sizeof(char));
	if (dst == 0)
		return (NULL);
	while (i < src_l)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
