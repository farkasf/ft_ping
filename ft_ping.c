/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:09:01 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/14 03:17:15 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

volatile sig_atomic_t   g_sig_status = 1;

void    sig_handler(int signum)
{
    if (signum == SIGINT)
        g_sig_status = 0;
}

void    ping_setup(t_ping *ping)
{
    if (setup_socket(ping) == -1 || get_socket_ip(ping) == -1)
    {
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
    printf("%s\n", ping.network.host_ip);

    signal(SIGINT, &sig_handler);
    
    while (1)
    {
        //ping
        //wait a bit
        if (g_sig_status == 0)
            break ;
    }

    //print the log
    
    free_struct(&ping);
    exit(EXIT_SUCCESS);
}