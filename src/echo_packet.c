/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 08:46:08 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/13 05:15:43 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

static unsigned short	checksum(void *header, int size)
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

void	receive_echo_reply(t_ping *ping, t_reply *reply)
{
	socklen_t			addr_size;
	struct sockaddr_in	recv_addr;
	struct timeval		timeout;

 	timeout.tv_sec = 0;
 	timeout.tv_usec = 500000;
 	setsockopt(ping->network.socket_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
	addr_size = sizeof(recv_addr);
	reply->recv_bytes = recvfrom(ping->network.socket_fd, reply->recv_data, \
		sizeof(reply->recv_data), 0, (struct sockaddr *)&recv_addr, &addr_size);
	if (reply->recv_bytes == -1)
	{
		if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
		{
			reply->socket_timeout = 1;
			return ;
		}
		dprintf(STDERR_FILENO, "ft_ping: recvfrom failed\n");
		free_struct(ping);
		exit(EXIT_FAILURE);
	}
	gettimeofday(&(ping->timer.rtt_finish), NULL);
}

void	send_echo_request(t_ping *ping)
{
	char			req_packet[ICMP_HDRLEN + ping->options.data_len];
	struct icmp		*header;
	ssize_t			sent_bytes;

	ft_memset(&req_packet, 0, sizeof(req_packet));
	header = (struct icmp *)req_packet;
	header->icmp_type = ICMP_ECHO;
	header->icmp_code = 0;
	header->icmp_id = htons(ping->network.pid);
	header->icmp_seq = htons(ping->network.sequence);
	ping->network.sequence++;
	header->icmp_cksum = checksum(req_packet, sizeof(req_packet));

	gettimeofday(&(ping->timer.rtt_start), NULL);
	sent_bytes = sendto(ping->network.socket_fd, &req_packet, sizeof(req_packet), 0, \
		(struct sockaddr *)&ping->network.remote_addr, sizeof(ping->network.remote_addr));
	if (sent_bytes == -1)
	{
		dprintf(STDERR_FILENO, "ft_ping: sendto failed\n");
		free_struct(ping);
		exit(EXIT_FAILURE);
	}
}
