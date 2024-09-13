/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:09:01 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/14 01:27:29 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	int		i;
	int		src_l;

	i = 0;
	src_l = strlen(src);
	dst = (char *)malloc((src_l + 1) * sizeof(char));
	if (dst == 0)
		return (NULL);
	while (i < src_l)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

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

int set_packet_lifetime(int socket_fd)
{
    int ttl;

    ttl = DEF_TTL;
    if (setsockopt(socket_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) == -1)
        return (-1);
    return (0);
}

int resolve_host(char *hostname, struct addrinfo **res)
{
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_ICMP;

    if (getaddrinfo(hostname, NULL, &hints, res) == -1 || *res == NULL)
        return (-1);
    
    return (0);
}

int get_socket_ip(t_ping *ping)
{
    struct addrinfo *res;

    if (resolve_host(ping->network.hostname, &res) == -1)
    {
        dprintf(STDERR_FILENO, "ft_ping: name or service not known\n");
        return (-1);
    }

    if (res->ai_addrlen != sizeof(ping->network.remote_addr))
    {
        dprintf(STDERR_FILENO, "ft_ping: address length mismatch\n");
        freeaddrinfo(res);
        return (-1);
    }
    memcpy(&ping->network.remote_addr, res->ai_addr, res->ai_addrlen);
    
    if (inet_ntop(AF_INET, &ping->network.remote_addr.sin_addr, ping->network.host_ip, INET_ADDRSTRLEN) == NULL)
    {
        dprintf(STDERR_FILENO, "ft_ping: failed to convert IP address to string format\n");
        freeaddrinfo(res);
        return (-1);
    }

    freeaddrinfo(res);
    return (0);
}

int setup_socket(t_ping *ping)
{
    ping->network.socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (ping->network.socket_fd == -1)
    {
        dprintf(STDERR_FILENO, "ft_ping: failed to create raw socket for ICMP\n");
        return (-1);
    }

    if (set_packet_lifetime(ping->network.socket_fd) == -1)
    {
        dprintf(STDERR_FILENO, "ft_ping: failed to set TTL on the raw socket for ICMP\n");
        return (-1);
    }
    
    return (0);
}

void    ping_setup(t_ping *ping)
{
    if (setup_socket(ping) == -1 || get_socket_ip(ping) == -1)
    {
        free_struct(ping);
        exit(EXIT_FAILURE);
    }
}

void check_option(t_ping *ping, char *flag)
{
    int i;

    i = 1;
    if (!flag[i])
    {
        free_struct(ping);
        print_usage();
    }
    while (flag[i])
    {
        if (flag[i] == 'v')
            ping->options.verbose = 1;
        else if (flag[i] == '?')
            ping->options.help = 1;
        else
        {
            dprintf(STDERR_FILENO, "ft_ping: unknown option -- '%c'\n", flag[i]);
            free_struct(ping);
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void parse_args(t_ping *ping, int ac, char **av)
{
    int i;

    i = 1;
    while (i < ac)
    {
        if (av[i][0] == '-' && strlen(av[i]) > 0)
            check_option(ping, av[i]);
        else
        {
            if (ping->network.hostname != NULL)
            {
                dprintf(STDERR_FILENO, "ft_ping: multiple destination addresses\n");
                free_struct(ping);
                exit(EXIT_FAILURE);
            }
            ping->network.hostname = ft_strdup(av[i]);
        }
        i++;
    }
    if (ping->options.help == 1)
    {
        free_struct(ping);
        print_usage();
    }
    if (ping->network.hostname == NULL || strlen(ping->network.hostname) == 0)
    {
        dprintf(STDERR_FILENO, "ft_ping: destination address required\n");   
        free_struct(ping);
        exit(EXIT_FAILURE);
    }
}

int main(int ac, char **av)
{
    t_ping  ping;

    check_uid();
    memset(&ping, 0, sizeof(t_ping));
    parse_args(&ping, ac, av);
    ping_setup(&ping);
    //printf("%s\n", ping.network.host_ip);
    free_struct(&ping);
}