/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:09:01 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/13 05:10:51 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

volatile sig_atomic_t	g_sig_status = 1;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		g_sig_status = 0;
}

static void	ping_setup(t_ping *ping)
{
	if (setup_socket(ping) == -1 || get_socket_ip(ping) == -1)
	{
		free_struct(ping);
		exit(EXIT_FAILURE);
	}
	ping->network.sequence = 0;
	ping->network.packets_sent = 0;
	ping->network.packets_received = 0;
	ping->network.pid = getpid();
	
	ping->stats.min_t = 0;
	ping->stats.max_t = 0;
	ping->stats.total_t = 0;
	ping->stats.total_t_sq = 0;

	if (!ping->options.delay)
		ping->options.delay = DEF_DELAY;
	if (!ping->options.set_packet_size)
		ping->options.data_len = ICMP_DATALEN;
}

int	main(int ac, char **av)
{
	t_ping			ping;
	unsigned int	i;

	i = 0;
	check_uid();
	ft_memset(&ping, 0, sizeof(t_ping));
	parse_args(&ping, ac, av);

	signal(SIGINT, &sig_handler);

	while (i < ping.hosts.host_count)
	{
		ping.network.hostname = ft_strdup(ping.hosts.hostnames[i]);
		ping_setup(&ping);
		print_ping_header(&ping);
		while (1)
		{
			ping_routine(&ping);
			if (g_sig_status == 0 || (ping.network.packets_sent == ping.options.max_packets && ping.network.packets_sent > 0))
				break ;
		}
		print_ping_stats(&ping);
		free_struct(&ping);
		i++;
	}

	exit(EXIT_SUCCESS);
}
