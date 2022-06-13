/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:50:25 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/24 15:46:25 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*next;

	if (lst == NULL || del == NULL)
		return ;
	elem = *lst;
	while (elem)
	{
		next = elem->next;
		ft_lstdelone(elem, del);
		elem = next;
	}
	*lst = NULL;
}
