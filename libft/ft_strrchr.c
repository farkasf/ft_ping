/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:03:25 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/24 17:18:55 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	if (s == 0)
		return (NULL);
	i = 0;
	p = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			p = ((char *) &s[i]);
		i++;
	}
	if ((char) c == s[i])
		p = ((char *) &s[i]);
	return (p);
}
