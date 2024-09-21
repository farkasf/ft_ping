/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:04:13 by ffarkas           #+#    #+#             */
/*   Updated: 2023/08/14 23:03:51 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_lst)
{
	t_list	*last;

	if (*lst == 0)
		*lst = new_lst;
	else
	{
		last = ft_lstlast(*(lst));
		last->next = new_lst;
	}
}
