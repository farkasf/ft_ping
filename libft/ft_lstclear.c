/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 08:09:47 by ffarkas           #+#    #+#             */
/*   Updated: 2023/08/14 23:00:57 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*pult;
	t_list	*temp;

	if (*lst == 0)
		return ;
	pult = *lst;
	temp = NULL;
	while (pult)
	{
		temp = pult;
		pult = pult->next;
		free(temp);
	}
	*lst = NULL;
}
