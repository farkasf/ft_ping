/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 23:07:03 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/17 00:08:02 by ffarkas          ###   ########.fr       */
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

