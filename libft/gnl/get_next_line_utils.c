/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:11:16 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/27 05:20:36 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* -----------------------------------------------------------------------
**		gnl_lstnew
**
**	Creates a new element of our list of file descriptors.
**
**	See get_next_list.h for a description of each of the element's members.
**
**	buffer does not need to be initialized.
**
**	- fd		file descriptor of the new element
** -------------------------------------------------------------------- */
static t_listfd	*gnl_lstnew(int fd)
{
	t_listfd	*new;

	new = malloc(sizeof(*new));
	if (! new)
		return (NULL);
	new->fd = fd;
	new->size = 0;
	new->index = 0;
	new->next = NULL;
	return (new);
}

/* -----------------------------------------------------------------------
**		gnl_lstadd
**
**	Used to fill our list of file descriptors.
**
**	This will be called when we encounter a new file descriptor.
**
**	An element corresponding to this file descriptor will then
**		be created, initialized, and added to the list.
**
**	- list		list of file descriptors
**	- fd		file descriptor to add to the list
** -------------------------------------------------------------------- */
void	gnl_lstadd(t_listfd **list, int fd)
{
	t_listfd	*new;

	new = gnl_lstnew(fd);
	if (! new)
		return ;
	new->next = *list;
	*list = new;
}

/* -----------------------------------------------------------------------
**		gnl_lstseek
**
**	Finds and returns the element in our list which corresponds
**		to the file descriptor.
**
**	- list		list of file descriptors and their data
**	- fd		file descriptor to find
** -------------------------------------------------------------------- */
t_listfd	*gnl_lstseek(t_listfd *list, int fd)
{
	while (list && list->fd != fd)
		list = list->next;
	return (list);
}

/* -----------------------------------------------------------------------
**		gnl_lstdel
**
**	Frees and deletes an element from the list of file descriptors.
**
**	Used when we reach the end of a file.
**
**	- list		list of file descriptors
**	- data		element to delete in the list
** -------------------------------------------------------------------- */
void	gnl_lstdel(t_listfd **list, t_listfd *data)
{
	t_listfd	*elem;

	if (*list == data)
		*list = data->next;
	else
	{
		elem = *list;
		while (elem->next != data)
			elem = elem->next;
		elem->next = data->next;
	}
	free(data);
}
