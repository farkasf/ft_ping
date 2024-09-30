/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:05:47 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/30 04:08:02 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

int	set_packet_lifetime(t_ping *ping)
{
	if (!ping->options.ttl)
		ping->options.ttl = DEF_TTL;
	if (setsockopt(ping->network.socket_fd, IPPROTO_IP, IP_TTL, &ping->options.ttl, sizeof(ping->options.ttl)) == -1)
		return (-1);
	return (0);
}

int resolve_host(char *hostname, struct addrinfo **res)
{
	struct addrinfo hints;

	*res = NULL;
	ft_memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;

	if (getaddrinfo(hostname, NULL, &hints, res) == -1 || *res == NULL)
		return (-1);

	return (0);
}

//consider implementing custom freeaddrinfo
int get_socket_ip(t_ping *ping)
{
	struct addrinfo *res;

	if (resolve_host(ping->network.hostname, &res) == -1)
	{
		dprintf(STDERR_FILENO, "ft_ping: unknown host\n");
		return (-1);
	}

	if (res->ai_addrlen != sizeof(ping->network.remote_addr))
	{
		dprintf(STDERR_FILENO, "ft_ping: address length mismatch\n");
		return (-1);
	}
	memcpy(&ping->network.remote_addr, res->ai_addr, res->ai_addrlen);

	if (inet_ntop(AF_INET, &ping->network.remote_addr.sin_addr, ping->network.host_ip, INET_ADDRSTRLEN) == NULL)
	{
		dprintf(STDERR_FILENO, "ft_ping: failed to convert IP address to string format\n");
		freeaddrinfo(res);
		return (-1);
	}

	freeaddrinfo(res);
	return (0);
}

int setup_socket(t_ping *ping)
{
	ping->network.socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (ping->network.socket_fd == -1)
	{
		dprintf(STDERR_FILENO, "ft_ping: failed to create raw socket for ICMP\n");
		return (-1);
	}

	if (set_packet_lifetime(ping) == -1)
	{
		dprintf(STDERR_FILENO, "ft_ping: failed to set TTL on the raw socket for ICMP\n");
		return (-1);
	}

	return (0);
}
