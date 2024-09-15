/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:44:42 by ffarkas           #+#    #+#             */
/*   Updated: 2024/09/15 17:04:00 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ping.h"

void	ping_routine(t_ping *ping)
{
	t_reply	echo_reply;

	memset(&echo_reply, 0, sizeof(t_reply));
	send_echo_request(ping);
	receive_echo_reply(ping, &echo_reply);

	usleep(1000000);
	return ; 
}
