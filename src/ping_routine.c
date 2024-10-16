/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:44:42 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/13 01:36:40 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

static void	update_stats(t_ping *ping, const t_reply *reply)
{
	if (reply->rrt < ping->stats.min_t || ping->stats.min_t == 0)
		ping->stats.min_t = reply->rrt;
	else if (reply->rrt > ping->stats.max_t)
		ping->stats.max_t = reply->rrt;

	ping->stats.total_t += reply->rrt;
	ping->stats.total_t_sq += reply->rrt * reply->rrt;
}

static void	calculate_rrt(t_ping *ping, t_reply *reply)
{
	double	seconds;
	double	useconds;

	seconds = ping->timer.rtt_finish.tv_sec - ping->timer.rtt_start.tv_sec;
	useconds = ping->timer.rtt_finish.tv_usec - ping->timer.rtt_start.tv_usec;

	reply->rrt = seconds * 1000 + useconds / 1000;
}

static void	analyze_reply(t_ping *ping, t_reply *reply)
{
	struct iphdr	*ip_hdr;
	struct icmphdr	*icmp_hdr;

	ip_hdr = (struct iphdr*)reply->recv_data;
	icmp_hdr = (struct icmphdr*)(reply->recv_data + (ip_hdr->ihl * 4));

	if (icmp_hdr->type == ICMP_ECHO)
		return ;

	if (icmp_hdr->type == ICMP_ECHOREPLY && ntohs(icmp_hdr->un.echo.id) == ping->network.pid)
	{
		reply->success = 1;
		ping->network.packets_received++;
	}
	else
	{
		reply->success = -1;
		reply->type = icmp_hdr->type;
		reply->code = icmp_hdr->code;
		reply->ip_dump = ip_hdr;
	}

	ping->network.packets_sent++;
	reply->recv_ttl = ip_hdr->ttl;
	reply->sequence = ntohs(icmp_hdr->un.echo.sequence);
}

void	ping_routine(t_ping *ping)
{
	t_reply	echo_reply;

	ft_memset(&echo_reply, 0, sizeof(t_reply));
	echo_reply.success = 0;
	echo_reply.socket_timeout = 0;

	gettimeofday(&(ping->timer.begin), NULL);

	send_echo_request(ping);
	receive_echo_reply(ping, &echo_reply);
	analyze_reply(ping, &echo_reply);

	if (echo_reply.success == 0)
		return ;

	calculate_rrt(ping, &echo_reply);
	update_stats(ping, &echo_reply);

	if (!ping->options.quiet)
		print_ping_response(ping, &echo_reply);

	if (echo_reply.success == -1 && ping->options.verbose == 1 && !echo_reply.socket_timeout)
		print_detailed_err_log(ping, &echo_reply);

	gettimeofday(&(ping->timer.end), NULL);
	ping->timer.elapsed_time = (ping->timer.end.tv_sec - ping->timer.begin.tv_sec) * 1000000 + (ping->timer.end.tv_usec - ping->timer.begin.tv_usec);
	if (ping->timer.elapsed_time < 1000000 * ping->options.delay && ping->network.packets_sent != ping->options.max_packets)
		usleep((1000000 * ping->options.delay) - ping->timer.elapsed_time);
}
