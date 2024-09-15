/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:51:44 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/15 21:24:16 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

void	print_ping_header(t_ping *ping)
{
	dprinf(STDOUT_FILENO, "PING %s (%s): %d data bytes\n", ping->network.hostname, ping->network.host_ip, ICMP_DATALEN);
}

void	print_ping_response(t_ping *ping, t_reply *reply)
{
	int 		bytes;
	uint16_t	sequence;

	bytes = reply->recv_bytes - IP_HDRLEN;
	sequence = ntohs(reply->sequence);
	dprintf(STDOUT_FILENO, "%d bytes from %s: icmp_seq=%d, ttl=%d, time=?ms\n", bytes, ping->network.host_ip, sequence, ping->options.ttl);
}
