/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:09:08 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/15 21:26:39 by ffarkas          ###   ########.fr       */
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
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>

# define DEF_TTL 64
# define IP_HDRLEN 20
# define ICMP_HDRLEN 8
# define ICMP_DATALEN 56
# define ICMP_PACKETLEN (ICMP_HDRLEN+ICMP_DATALEN)
# define ICMP_MAX_PACKETLEN (1500 - IP_HDRLEN - ICMP_HDRLEN)

typedef struct s_network
{
	int					socket_fd;
	struct sockaddr_in	remote_addr;
	char				host_ip[INET_ADDRSTRLEN];
	char				*hostname;
	unsigned int		packets_sent;
	unsigned int		packets_received;
}	t_network;

typedef struct s_options
{
	unsigned int	help;
	unsigned int	verbose;
	int				ttl;
}	t_options;

typedef struct s_reply
{
	char			recv_data[ICMP_MAX_PACKETLEN];
	ssize_t			recv_bytes;
	int				code;
	int				type;
	unsigned int	success;
	uint16_t		sequence;
}	t_reply;

typedef struct s_timer
{
	struct timeval	begin;
	struct timeval	rtt_start;
	struct timeval	rtt_finish;
}	t_timer;

typedef struct s_ping
{
	t_options	options;
	t_network	network;
	t_timer		timer;
}	t_ping;

void			print_usage(void);
void			free_struct(t_ping *ping);
void			check_uid(void);

char			*ft_strdup(const char *src);
void			check_option(t_ping *ping, char *flag);
void			parse_args(t_ping *ping, int ac, char **av);

int				set_packet_lifetime(int socket_fd);
int				resolve_host(char *hostname, struct addrinfo **res);
int				get_socket_ip(t_ping *ping);
int				setup_socket(t_ping *ping);

void			ping_routine(t_ping *ping);
void			analyze_reply(t_reply *reply);

void			receive_echo_reply(t_ping *ping, t_reply *reply);
void			send_echo_request(t_ping *ping);
unsigned short	checksum(void *header, int size);

void			print_ping_header(t_ping *ping);
void			print_ping_response(t_ping *ping, t_reply *reply);

#endif
