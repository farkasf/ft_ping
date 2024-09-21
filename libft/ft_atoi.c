/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:59:16 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/14 04:05:47 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *ptr)
{
	int	temp;
	int	sign;
	int	i;

	temp = 0;
	sign = 1;
	i = 0;
	while (ptr[i] == ' ' || (ptr[i] >= 9 && ptr[i] <= 13))
		i++;
	if (ptr[i] == '-')
		sign = -1;
	if (ptr[i] == '-' || ptr[i] == '+')
		i++;
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		temp = temp * 10 + ptr[i] - '0';
		i++;
	}
	return (temp * sign);
}
