/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:44:42 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/15 12:01:10 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

void	ping_routine(t_ping *ping)
{
	printf("resolved: %s\n", ping->network.host_ip);
	send_echo_request(ping);
	usleep(1000000);
	return ; 
}
