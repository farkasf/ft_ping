/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:09:01 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/12 16:39:46 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

volatile sig_atomic_t	g_sig_status = 1;

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		g_sig_status = 0;
}

void	ping_setup(t_ping *ping)
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
	if (!ping->options.data_len)
		ping->options.data_len = ICMP_DATALEN;
}

int main(int ac, char **av)
{
	t_ping  ping;

	check_uid();
	ft_memset(&ping, 0, sizeof(t_ping));
	parse_args(&ping, ac, av);

	ping_setup(&ping);

	signal(SIGINT, &sig_handler);
	print_ping_header(&ping);

	while (1)
	{
		ping_routine(&ping);
		if (g_sig_status == 0 || ping.network.packets_sent == ping.options.max_packets)
			break ;
	}

	print_ping_stats(&ping);

	free_struct(&ping);
	exit(EXIT_SUCCESS);
}


/*
	printf("addr: %s\n", ping.network.hostname);
	printf("quiet: %d | verbose: %d | help: %d\n", ping.options.quiet, ping.options.verbose, ping.options.help);
	printf("ttl: %d | packets: %d\n", ping.options.ttl, ping.options.max_packets);
*/
