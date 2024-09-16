/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:04:31 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/16 14:54:38 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	int		i;
	int		src_l;

	i = 0;
	src_l = strlen(src);
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

void check_option(t_ping *ping, char *flag)
{
	int i;

	i = 1;
	if (!flag[i])
	{
		free_struct(ping);
		print_usage();
	}
	while (flag[i])
	{
		if (flag[i] == 'v')
			ping->options.verbose = 1;
		else if (flag[i] == '?')
			ping->options.help = 1;
		else
		{
			dprintf(STDERR_FILENO, "ft_ping: invalid option -- '%c'\n", flag[i]);
			dprintf(STDERR_FILENO, "Try './ft_ping -?' for more information.\n");
			free_struct(ping);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void parse_args(t_ping *ping, int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-' && strlen(av[i]) > 0)
			check_option(ping, av[i]);
		else
		{
			if (ping->network.hostname != NULL)
				continue ;
			ping->network.hostname = ft_strdup(av[i]);
		}
		i++;
	}
	if (ping->options.help == 1)
	{
		print_usage();
		free_struct(ping);
	}
	if (ping->network.hostname == NULL || strlen(ping->network.hostname) == 0)
	{
		dprintf(STDERR_FILENO, "ft_ping: missing host operand\n");
		dprintf(STDERR_FILENO, "Try './ft_ping -?' for more information.\n");
		free_struct(ping);
		exit(EXIT_FAILURE);
	}
}
