/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:09:08 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/14 03:09:00 by ffarkas          ###   ########.fr       */
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

typedef struct s_timer
{
    struct timeval  begin;
    struct timeval  rtt_start;
    struct timeval  rtt_finish;
}   t_timer;

typedef struct s_ping
{
    t_options   options;
    t_network   network;
}   t_ping;

void    print_usage(void);
void    free_struct(t_ping *ping);
void    check_uid(void);

char	*ft_strdup(const char *src);
void    check_option(t_ping *ping, char *flag);
void    parse_args(t_ping *ping, int ac, char **av);

int     set_packet_lifetime(int socket_fd);
int     resolve_host(char *hostname, struct addrinfo **res);
int     get_socket_ip(t_ping *ping);
int     setup_socket(t_ping *ping);


#endif