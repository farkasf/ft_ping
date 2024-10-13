/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:04:31 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/13 02:28:51 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

static void	check_option(t_ping *ping, char *flag)
{
	int i;

	i = 1;
	if (!flag[i])
		return ;
	switch (flag[i])
	{
		case 'v':
			ping->options.verbose = 1;
			break ;
		case '?':
			ping->options.help = 1;
			break ;
		case 'q':
			ping->options.quiet = 1;
			break ;
		default:
			print_formatted_error(ping, "ft_ping: invalid option -- '%s'\nTry './ft_ping -?' for more information.\n", &flag[i]);
	}
}

static unsigned int	check_num(t_ping *ping, char *ptr, size_t max_val, bool zero, char mode)
{
	unsigned long	value;
	int				i;
	int				sign;

	value = 0;
	sign = 1;
	i = 0;

	if (ft_strlen(ptr) > 1)
	{
		if (ptr[i] == '-')
			sign = -1;
		if (ptr[i] == '-' || ptr[i] == '+')
			i++;	
	}
	while (ptr[i])
	{
		if (!ft_isdigit(ptr[i]))
		{
			dprintf(STDERR_FILENO, "ft_ping: invalid value (`%s' near `%s')\n", ptr, ptr);
			free_struct(ping);
			exit(EXIT_FAILURE);
		}
		value = value * 10 + ptr[i] - '0';
		i++;
	}
	value *= sign;
	if ((value == 0 && !zero) || (ptr[0] == '-' && mode == 'i'))
		print_formatted_error(ping, "ft_ping: option value too small: %s\n", ptr);
	if (max_val && value > max_val)
		print_formatted_error(ping, "ft_ping: option value too big: %s\n", ptr);
	return ((unsigned int)value);
}

void parse_args(t_ping *ping, int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i] == NULL || ft_strlen(av[i]) == 0)
		{
			i++;
			continue ;
		}
		else if (!ft_strncmp(av[i], "--ttl", 5))
		{
			if (ft_strlen(av[i]) != 6 && ft_strlen(av[i]) != 5)
				ping->options.ttl = check_num(ping, av[i] + 6, 255, 0, 't');
			else if (av[i + 1])
			{
				ping->options.ttl = check_num(ping, av[i + 1], 255, 0, 't');
				i++;
			}
			else
				print_formatted_error(ping, "ft_ping: option '--ttl' requires an argument\nTry './ft_ping -?' for more information.\n", NULL);
		}
		else if (av[i][0] == '-' && ft_strlen(av[i]) > 1)
		{
			if (av[i][1] == 'c')
			{
				if (ft_strlen(av[i]) != 2)
					ping->options.max_packets = check_num(ping, av[i] + 2, 0, 1, 'c');
				else if (av[i + 1])
				{
					ping->options.max_packets = check_num(ping, av[i + 1], 0, 1, 'c');
					i++;
				}
				else
					print_formatted_error(ping, "ft_ping: option requires an argument -- 'c'\nTry './ft_ping -?' for more information.\n", NULL);
			}
			else if (av[i][1] == 'i')
			{
				if (ft_strlen(av[i]) != 2)
					ping->options.delay = check_num(ping, av[i] + 2, 0, 0, 'i');
				else if (av[i + 1])
				{
					ping->options.delay = check_num(ping, av[i + 1], 0, 0, 'i');
					i++;
				}
				else
					print_formatted_error(ping, "ft_ping: option requires an argument -- 'i'\nTry './ft_ping -?' for more information.\n", NULL);
			}
			else if (av[i][1] == 's')
			{
				ping->options.set_packet_size = 1;
				if (ft_strlen(av[i]) != 2)
					ping->options.data_len = check_num(ping, av[i] + 2, ICMP_MAX_PACKETLEN, 1, 's');
				else if (av[i + 1])
				{
					ping->options.data_len = check_num(ping, av[i + 1], ICMP_MAX_PACKETLEN, 1, 's');
					i++;
				}
				else
					print_formatted_error(ping, "ft_ping: option requires an argument -- 's'\nTry './ft_ping -?' for more information.\n", NULL);
			}
			else
				check_option(ping, av[i]);
		}
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
		print_formatted_error(ping, "ft_ping: missing host operand\nTry './ft_ping -?' for more information.\n", NULL);
}
