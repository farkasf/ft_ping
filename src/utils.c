/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:06:25 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/12 15:21:16 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

void	print_usage(void)
{
	dprintf(STDOUT_FILENO, "Usage: ./ft_ping [OPTION...] HOST ...\n");
	dprintf(STDOUT_FILENO, "Send ICMP ECHO_REQUEST packets to network hosts.\n\n");
	dprintf(STDOUT_FILENO, " Options valid for --echo requests:\n\n");
	dprintf(STDOUT_FILENO, "  -?           gives this help list\n");
	dprintf(STDOUT_FILENO, "  -v           verbose output\n");
	dprintf(STDOUT_FILENO, "  -q           quiet output\n");
	dprintf(STDOUT_FILENO, "  -c NUMBER    stop after sending NUMBER packets\n");
	dprintf(STDOUT_FILENO, "  -i NUMBER    wait NUMBER seconds between sending each packet\n");
	dprintf(STDOUT_FILENO, "  --ttl=N      specify N as time-to-live\n\n");
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

void check_uid(void)
{
	if (getuid() == 0)
		return ;
	dprintf(STDERR_FILENO, "ft_ping: user not root\n");
	exit(EXIT_FAILURE);
}
