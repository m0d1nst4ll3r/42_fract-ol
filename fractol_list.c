/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:12:25 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/11 17:19:04 by rpohlen          ###   ########.fr       */
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

//	Used to seek a specific color in the list
t_color	*fractol_lstseek(t_color *lst, char *name)
{
	while (lst && ft_strcmp(lst->name, name))
		lst = lst->next;
	return (lst);
}

//	Used for color swapping
//	If elem is the last element of the list, go back to first
t_color	*fractol_lstnext(t_color *lst, t_color *elem)
{
	if (elem->next)
		return (elem->next);
	return (lst);
}

//	Used for color swapping
//	If elem is the first element of the list, the last one will
//		be returned
t_color	*fractol_lstprev(t_color *lst, t_color *elem)
{
	while (lst->next && lst->next != elem)
		lst = lst->next;
	return (lst);
}
