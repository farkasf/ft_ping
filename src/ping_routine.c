/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:44:42 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/15 22:49:54 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

void	analyze_reply(t_ping *ping, t_reply *reply)
{
	struct iphdr	*ip_hdr;
	struct icmphdr	*icmp_hdr;

	ip_hdr = (struct iphdr*)reply->recv_data;
	icmp_hdr = (struct icmphdr*)(reply->recv_data + (ip_hdr->ihl * 4));
	
	if (icmp_hdr->type == ICMP_ECHOREPLY && ntohs(icmp_hdr->un.echo.id) == ping->network.pid)
		reply->success = 1;
	else
	{
		if (icmp_hdr->type != ICMP_ECHO)
			reply->success = -1;
		reply->code = icmp_hdr->code;
		reply->type = icmp_hdr->type;
	}

	reply->sequence = ntohs(icmp_hdr->un.echo.sequence);
}

void	ping_routine(t_ping *ping)
{
	t_reply	echo_reply;

	memset(&echo_reply, 0, sizeof(t_reply));
	echo_reply.success = 0;

	send_echo_request(ping);
	receive_echo_reply(ping, &echo_reply);
	analyze_reply(ping, &echo_reply);

	if (echo_reply.success == 1)
	{
		dprintf(STDOUT_FILENO, "successfully exchanged echo\n");
		print_ping_response(ping, &echo_reply);
	}
	else if (echo_reply.success == -1)
	{
		dprintf(STDOUT_FILENO, "data transfer error\n");
		//a place for verbose error output
	}

	usleep(1000000);
	return ; 
}
