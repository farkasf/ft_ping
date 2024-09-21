/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:53:23 by ffarkas           #+#    #+#             */
/*   Updated: 2023/04/06 22:32:07 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_c(va_list *args)
{
	char	c;

	c = va_arg(*args, int);
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_print_s(va_list *args)
{
	char	*str;
	int		count;

	count = 1;
	str = va_arg(*args, char *);
	if (str == 0)
		str = "(null)";
	ft_putstr_fd(str, 1);
	count = ft_strlen(str);
	return (count);
}

int	ft_print_percent(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}

int	ft_numlen(unsigned int num)
{
	int	len;

	len = 0;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}
