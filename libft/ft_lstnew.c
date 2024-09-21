/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 07:56:48 by ffarkas           #+#    #+#             */
/*   Updated: 2023/08/15 12:11:17 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int number)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == 0)
		return (NULL);
	new->num = number;
	new->id = -1;
	new->signal = 0;
	new->next = NULL;
	return (new);
}
