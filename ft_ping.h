/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:09:08 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/14 01:29:29 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include <errno.h>
# include <signal.h>

# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/ip_icmp.h>

# define DEF_TTL 64

typedef struct s_network
{
    int                 socket_fd;
    struct sockaddr_in  remote_addr;
    char                host_ip[INET_ADDRSTRLEN];
    char                *hostname;
}   t_network;

typedef struct s_options
{
    unsigned int    help;
    unsigned int    verbose;
}   t_options;

typedef struct s_ping
{
    t_options   options;
    t_network   network;
}   t_ping;

#endif