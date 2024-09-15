/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 08:46:08 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/15 12:03:30 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

unsigned short	checksum(void *header, int size)
{
	unsigned short	*buf;
	unsigned short	checksum;
	unsigned int	sum;

	buf = (unsigned short *)header;
	sum = 0;
	while (size > 1)
	{
		sum += *buf++;
		size -= 2;
	}
	if (size == 1)
		sum += *(unsigned char *)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	checksum = ~sum;
	return (checksum);
}

void	send_echo_request(t_ping *ping)
{
	char			packet[ICMP_PACKET];
	struct icmp		*header;
	ssize_t			sent_bytes;

	header = (struct icmp *)packet;
	header->icmp_type = ICMP_ECHO;
	header->icmp_code = 0;
	header->icmp_id = htons(getpid());
	//init packets send to 0 at the beginning
	ping->network.packets_sent++;
	header->icmp_seq = htons(ping->network.packets_sent);
	header->icmp_cksum = checksum(packet, sizeof(packet));
	
	sent_bytes = sendto(ping->network.socket_fd, &packet, sizeof(packet), 0, (struct sockaddr *)&ping->network.remote_addr, sizeof(ping->network.remote_addr));
	if (sent_bytes < 0)
	{
		dprintf(STDERR_FILENO, "ft_ping: sendto failed\n");
		free_struct(ping);
		exit(EXIT_FAILURE);
	}
	else
	{
		dprintf(STDOUT_FILENO, "ft_ping: sent an echo request [%d] to %s\n", ping->network.packets_sent, ping->network.host_ip);
	}
}
