/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:12:25 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/22 13:36:43 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Adds an element at front of list
void	fractol_lstadd(t_color **lst, t_color *new)
{
	if (! new || ! lst)
		return ;
	new->next = *lst;
	*lst = new;
}

//	Frees everything in a t_color list
void	fractol_lstclear(t_color *lst)
{
	t_color	*elem;

	while (lst)
	{
		elem = lst->next;
		free(lst->name);
		free(lst->palette);
		free(lst);
		lst = elem;
	}
}