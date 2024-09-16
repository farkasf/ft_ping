/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:44 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/16 23:40:04 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

void	print_ping_header(t_ping *ping)
{
	dprintf(STDOUT_FILENO, "PING %s (%s): %d data bytes\n", ping->network.hostname, ping->network.host_ip, ICMP_DATALEN);
}

void	print_ping_response(t_ping *ping, t_reply *reply)
{
	int	bytes;

	bytes = reply->recv_bytes - IP_HDRLEN;
	dprintf(STDOUT_FILENO, "%d bytes from %s: ", bytes, ping->network.host_ip);
	if (reply->success == 1)
		dprintf(STDOUT_FILENO, "icmp_seq=%d ttl=%d time=%.3f ms\n", reply->sequence, ping->options.ttl, reply->rrt);
	else
		print_icmp_error(reply);

}

void	print_ping_stats(t_ping *ping)
{
	double	packet_loss;
	double	avg_t;
	double	variance;
	
	avg_t = ping->stats.total_t / ping->network.packets_sent;
	packet_loss = 1 - ((double)ping->network.packets_received / ping->network.packets_sent);
	variance = (ping->stats.total_t_sq / ping->network.packets_sent) - (avg_t * avg_t);

	dprintf(STDOUT_FILENO, "--- %s ping statistics ---\n%d packets transmitted, %d packets received, %.0f%% packet loss\n", 
		ping->network.hostname, ping->network.packets_sent, ping->network.packets_received, packet_loss * 100);

	if (packet_loss != 1)
		dprintf(STDOUT_FILENO, "rount-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", 
			ping->stats.min_t, avg_t, ping->stats.max_t, newton_sqrt(variance));
}
