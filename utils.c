/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:06:25 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/14 03:06:39 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void    print_usage(void)
{
    dprintf(STDOUT_FILENO, "Usage: ./ft_ping [OPTION...] HOST ...\n");
    dprintf(STDOUT_FILENO, "Send ICMP ECHO_REQUEST packets to network hosts.\n\n");
    dprintf(STDOUT_FILENO, "Options valid for all request types:\n\n");
    dprintf(STDOUT_FILENO, "  -?      gives this help list\n");
    dprintf(STDOUT_FILENO, "  -v      verbose output\n");
    exit(EXIT_SUCCESS);
}

void    free_struct(t_ping *ping)
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