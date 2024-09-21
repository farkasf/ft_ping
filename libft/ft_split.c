/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 23:11:40 by ffarkas           #+#    #+#             */
/*   Updated: 2023/01/19 21:24:57 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(const char *s, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
				i++;
			w++;
		}
	}
	return (w);
}

static int	ft_wlen(const char *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static char	*ft_cword(const char *s, char c, int *i)
{
	char	*w;
	int		k;

	k = 0;
	w = (char *)malloc((ft_wlen(s, c, *i) + 1) * sizeof(char));
	if (w == 0)
		return (NULL);
	while (s[*i] && s[*i] != c)
	{
		w[k] = s[*i];
		*i += 1;
		k++;
	}
	w[k] = '\0';
	return (w);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	str = (char **)malloc((ft_wcount(s, c) + 1) * sizeof(char *));
	if (str == 0)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			str[j] = ft_cword(s, c, &i);
			j++;
		}
	}
	str[j] = NULL;
	return (str);
}
