/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:25:16 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/17 01:30:38 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numsize(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		i++;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int c)
{
	unsigned int	size;
	char			*str;

	if (c == -2147483648)
		return (ft_strdup("-2147483648"));
	size = ft_numsize(c);
	str = malloc((size + 1) * sizeof(char));
	if (str == 0)
		return (NULL);
	str[size] = '\0';
	if (c == 0)
		str[0] = '0';
	if (c < 0)
	{
		str[0] = '-';
		c *= -1;
	}
	while (c)
	{
		str[size - 1] = (c % 10) + '0';
		c /= 10;
		size--;
	}
	return (str);
}
