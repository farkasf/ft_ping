/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_up.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:27:50 by ffarkas           #+#    #+#             */
/*   Updated: 2023/04/06 22:31:51 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa(unsigned int num)
{
	char	*str;
	int		len;

	len = ft_numlen(num);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == 0)
		return (NULL);
	str[len] = '\0';
	while (num)
	{
		str[len - 1] = num % 10 + '0';
		num /= 10;
		len --;
	}
	return (str);
}

int	ft_print_u(va_list *args)
{
	char			*str;
	unsigned int	num;
	int				count;

	num = va_arg(*args, unsigned int);
	count = 0;
	if (num == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	else
	{
		str = ft_uitoa(num);
		ft_putstr_fd(str, 1);
		count = ft_strlen(str);
		free (str);
	}
	return (count);
}

int	ft_ptrlen(unsigned long long ptr)
{
	int	len;

	len = 0;
	while (ptr)
	{
		ptr /= 16;
		len++;
	}
	return (len);
}

void	ft_putptr(unsigned long long int ptr)
{
	if (ptr >= 16)
	{
		ft_putptr(ptr / 16);
		ft_putptr(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar_fd((ptr + '0'), 1);
		else
			ft_putchar_fd((ptr - 10 + 'a'), 1);
	}
}

int	ft_print_p(va_list *args)
{
	unsigned long long int	ptr;
	int						count;

	ptr = va_arg(*args, unsigned long long int);
	count = 0;
	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	else
	{
		ft_putstr_fd("0x", 1);
		count += 2;
		ft_putptr(ptr);
		count += ft_ptrlen(ptr);
	}
	return (count);
}
