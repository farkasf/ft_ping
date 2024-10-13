/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:06:25 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/13 05:00:29 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

void	print_formatted_error(t_ping *ping, const char *format, const char *arg)
{
	dprintf(STDERR_FILENO, format, arg);
	free_struct(ping);
	exit(EXIT_FAILURE);
}

void	print_usage(t_ping *ping)
{
	dprintf(STDOUT_FILENO,
		"Usage: ./ft_ping [OPTION...] HOST ...\n"
		"Send ICMP ECHO_REQUEST packets to network hosts.\n\n"
		" Options valid for --echo requests:\n\n"
		"  -?           gives this help list\n"
		"  -v           verbose output\n"
		"  -q           quiet output\n"
		"  -c NUMBER    stop after sending NUMBER packets\n"
		"  -i NUMBER    wait NUMBER seconds between sending each packet\n"
		"  -s NUMBER    send NUMBER data octets\n"
		"  --ttl=N      specify N as time-to-live\n\n");
	free_struct(ping);
	exit(EXIT_SUCCESS);
}

double	newton_sqrt(double num)
{
	double	guess;
	double	epsilon;

	guess = num / 2.0;
	epsilon = 0.0001;
	while ((guess * guess - num > epsilon) || (num - guess * guess > epsilon))
		guess = (guess + num / guess) / 2.0;
	return (guess);
}

void	check_uid(void)
{
	if (getuid() == 0)
		return ;
	dprintf(STDERR_FILENO, "ft_ping: user not root\n");
	exit(EXIT_FAILURE);
}

void	free_struct(t_ping *ping)
{
	if (ping->network.socket_fd)
		close(ping->network.socket_fd);
	if (ping->network.hostname)
	{
		free(ping->network.hostname);
		ping->network.hostname = NULL;
	}
}
