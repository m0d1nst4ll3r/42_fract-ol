/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:11:36 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/27 17:44:59 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

# include <unistd.h>
# include <stdlib.h>

/* -----------------------------------------------------------------------
**		t_listfd
**
**	Contains all the data relevant to a single file descriptor,
**		which we have to save in-between get_next_line calls,
**		so that we can remember our buffer and our progression in it.
**
**	Used as a list so that we can remember several file descriptors,
**		and freely switch between them.
**
**	- fd		file descriptor to which the element corresponds
**	- buffer	its buffer that's getting filled by read calls
**	- size		size of this buffer returned by read calls
**	- index		our progression in this buffer
**	- next		other elements containing other file descriptors, or NULL
** -------------------------------------------------------------------- */
typedef struct s_listfd
{
	int				fd;
	char			buffer[BUFFER_SIZE];
	ssize_t			size;
	ssize_t			index;
	struct s_listfd	*next;
}					t_listfd;

char		*get_next_line(int fd);
void		gnl_lstadd(t_listfd **list, int fd);
t_listfd	*gnl_lstseek(t_listfd *list, int fd);
void		gnl_lstdel(t_listfd **list, t_listfd *data);

#endif
