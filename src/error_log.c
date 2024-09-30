/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:07:03 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/30 04:06:30 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

static const t_icmp_error	responses[] = {
	{ ICMP_DEST_UNREACH, ICMP_NET_UNREACH, "Destination Net Unreachable" },
	{ ICMP_DEST_UNREACH, ICMP_HOST_UNREACH, "Destination Host Unreachable" },
	{ ICMP_DEST_UNREACH, ICMP_PROT_UNREACH, "Destination Protocol Unreachable" },
	{ ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, "Destination Port Unreachable" },
	{ ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED, "Fragmentation needed and DF set" },
	{ ICMP_DEST_UNREACH, ICMP_SR_FAILED, "Source Route Failed" },
	{ ICMP_DEST_UNREACH, ICMP_NET_UNKNOWN, "Network Unknown" },
	{ ICMP_DEST_UNREACH, ICMP_HOST_UNKNOWN, "Host Unknown" },
	{ ICMP_DEST_UNREACH, ICMP_HOST_ISOLATED, "Host Isolated" },
	{ ICMP_DEST_UNREACH, ICMP_NET_UNR_TOS, "Destination Network Unreachable At This TOS" },

	{ ICMP_SOURCE_QUENCH, 0, "Source Quench" },

	{ ICMP_REDIRECT, ICMP_REDIR_NET, "Redirect Network" },
	{ ICMP_REDIRECT, ICMP_REDIR_HOST, "Redirect Host" },
	{ ICMP_REDIRECT, ICMP_REDIR_NETTOS, "Redirect Type of Service and Network" },
	{ ICMP_REDIRECT, ICMP_REDIR_HOSTTOS, "Redirect Type of Service and Host" },

	{ ICMP_TIME_EXCEEDED, ICMP_EXC_TTL, "Time to live exceeded" },
	{ ICMP_TIME_EXCEEDED, ICMP_EXC_FRAGTIME, "Frag reassembly time exceeded" },

	{ ICMP_PARAMETERPROB, 0, "Pointer Indicates Error" },
	{ ICMP_PARAMETERPROB, 1, "Missing Required Option" },

	{ ICMP_TIMESTAMPREPLY, 0, "Timestamp Reply" }
};

void	fetch_icmp_error(t_reply *reply)
{
	size_t	i;

	i = 0;
	while (i < (sizeof(responses) / sizeof(responses[0])))
	{
		if (responses[i].type == reply->type && responses[i].code == reply->code)
		{
			dprintf(STDOUT_FILENO, "%s\n", responses[i].err_msg);
			return ;
		}
		i++;
	}
}

void	print_detailed_err_log(t_ping *ping, t_reply *reply)
{
	size_t			i;

	i = 0;
	reply->ip_dump->tot_len = htons(IP_HDRLEN + ICMP_HDRLEN + ICMP_DATALEN);
	//reply->ip_dump->tot_len = htons(ntohs(reply->ip_dump->tot_len) - ICMP_HDRLEN - IP_HDRLEN);
	dprintf(STDOUT_FILENO, "IP Hdr Dump:\n");
	while (i < IP_HDRLEN)
	{
		dprintf(STDOUT_FILENO, " %02x%02x", ((unsigned char *)reply->ip_dump)[i], ((unsigned char *)reply->ip_dump)[i + 1]);
		i += 2;
	}
	dprintf(STDOUT_FILENO, "\nVr HL TOS  Len   ID Flg  off TTL Pro  cks      Src\tDst\tData\n");
	dprintf(STDOUT_FILENO," %1x  %1x  %02x %04x %04x   %1x %04x  %02x  %02x %04x %s  %s \n", 
		reply->ip_dump->version, reply->ip_dump->ihl, reply->ip_dump->tos, htons(reply->ip_dump->tot_len), ntohs(reply->ip_dump->id), 
		(ntohs(reply->ip_dump->frag_off) & 0xe000) >> 13, ntohs(reply->ip_dump->frag_off) & 0x1FFF, reply->ip_dump->ttl, reply->ip_dump->protocol, 
		ntohs(reply->ip_dump->check), inet_ntoa(*((struct in_addr *) &reply->ip_dump->daddr)), ping->network.host_ip);
	dprintf(STDOUT_FILENO, "ICMP: type 8, code 0, size %d, id 0x%04x, seq 0x%04x\n", 
		ICMP_PACKETLEN, (unsigned int)ping->network.pid, ping->network.packets_sent - 1);
}
