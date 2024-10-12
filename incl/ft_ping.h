/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:09:08 by ffarkas           #+#    #+#             */
/*   Updated: 2024/10/13 01:32:58 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# include <sys/time.h>
# include <errno.h>
# include <signal.h>

# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>

# define IP_HDRLEN 20
# define ICMP_HDRLEN 8
# define ICMP_DATALEN 56
# define ICMP_MAX_PACKETLEN (1500 - IP_HDRLEN - ICMP_HDRLEN)
# define DEF_TTL 64
# define DEF_DELAY 1

typedef struct s_network
{
	int					socket_fd;
	struct sockaddr_in	remote_addr;
	char				host_ip[INET_ADDRSTRLEN];
	char				*hostname;
	unsigned int		sequence;
	unsigned int		packets_sent;
	unsigned int		packets_received;
	pid_t				pid;
}	t_network;

typedef struct s_options
{
	bool				help;
	bool				verbose;
	bool				quiet;
	bool				flood;
	bool				set_packet_size;
	unsigned int		ttl;
	unsigned int		max_packets;
	unsigned int		delay;
	unsigned int		data_len;
}	t_options;

typedef struct s_reply
{
	struct iphdr	*ip_dump;
	char			recv_data[ICMP_MAX_PACKETLEN];
	ssize_t			recv_bytes;
	int				recv_ttl;
	int				type;
	int				code;
	int				success;
	uint16_t		sequence;
	double			rrt;
	bool			socket_timeout;
}	t_reply;

typedef struct s_timer
{
	struct timeval	begin;
	struct timeval	end;
	struct timeval	rtt_start;
	struct timeval	rtt_finish;
	long			elapsed_time;
}	t_timer;

typedef struct s_stats
{
	double	min_t;
	double	max_t;
	double	total_t;
	double	total_t_sq;
}	t_stats;

typedef struct s_icmp_error
{
	int		type;
	int		code;
	char	*err_msg;
}	t_icmp_error;

typedef struct s_ping
{
	t_options	options;
	t_network	network;
	t_timer		timer;
	t_stats		stats;
}	t_ping;

void			print_usage(void);
void			free_struct(t_ping *ping);
void			check_uid(void);
double			newton_sqrt(double num);

void			parse_args(t_ping *ping, int ac, char **av);

int				get_socket_ip(t_ping *ping);
int				setup_socket(t_ping *ping);

void			ping_routine(t_ping *ping);

void			receive_echo_reply(t_ping *ping, t_reply *reply);
void			send_echo_request(t_ping *ping);

void			print_ping_header(t_ping *ping);
void			print_ping_response(t_ping *ping, t_reply *reply);
void			print_ping_stats(t_ping *ping);

void			fetch_icmp_error(const t_reply *reply);
void			print_detailed_err_log(t_ping *ping, t_reply *reply);

#endif
