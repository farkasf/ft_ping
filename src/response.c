/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:44 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/15 23:52:16 by ffarkas          ###   ########.fr       */
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
	dprintf(STDOUT_FILENO, "%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", bytes, ping->network.host_ip, reply->sequence, ping->options.ttl, reply->rrt);
}
