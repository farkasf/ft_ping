/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:20:22 by ffarkas           #+#    #+#             */
/*   Updated: 2023/04/06 22:32:01 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_di(va_list *args)
{
	char	*str;
	int		num;
	int		count;

	num = va_arg(*args, int);
	str = ft_itoa(num);
	count = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free (str);
	return (count);
}

void	ft_puthex(unsigned int num, char format)
{
	if (num >= 16)
	{
		ft_puthex(num / 16, format);
		ft_puthex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (format == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			if (format == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	ft_hexlen(unsigned int num)
{
	int	len;

	len = 0;
	while (num)
	{
		num /= 16;
		len++;
	}
	return (len);
}

int	ft_print_x(va_list *args, char format)
{
	unsigned int	num;

	num = va_arg(*args, unsigned int);
	if (num == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	else
		ft_puthex(num, format);
	return (ft_hexlen(num));
}
