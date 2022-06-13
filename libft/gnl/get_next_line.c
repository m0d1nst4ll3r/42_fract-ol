/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:10:45 by rpohlen           #+#    #+#             */
/*   Updated: 2021/11/27 17:46:00 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* -----------------------------------------------------------------------
**		realloc_line
**
**	Duplicates old, if it exists, concatenates a portion of the
**		buffer to it, and frees old.
**
**	In this case, old represents the unfinished line we have started
**		writing, or NULL if we haven't written anything yet.
**
**	The portion of the buffer that will be concatenated is all or part
**		of the line, and will either stop at a newline, or at the end
**		of the buffer.
**
**	Note that this will be very inefficient when BUFFER_SIZE is 1.
**	However, this limitation is unavoidable.
**
**	- old		part of the line that has been written so far
**	- buffer	buffer of which a portion will be added to the line
**	- len		length of the portion to add
** -------------------------------------------------------------------- */
static char	*realloc_line(char *old, char *buffer, size_t len)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	while (old && old[i])
		i++;
	new = malloc((i + len + 1) * sizeof(*new));
	i = 0;
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	free(old);
	j = 0;
	while (j < len)
	{
		new[i + j] = buffer[j];
		j++;
	}
	new[i + j] = 0;
	return (new);
}

/* -----------------------------------------------------------------------
**		parse_buffer
**
**	Parses the file descriptor's buffer to its end (symbolized by
**		data->size), reallocating and filling the line as it goes.
**
**	Stops at the first newline encountered and returns 1.
**
**	Returns 0 if no newline is encountered, in which case this function
**		will be called again with a new buffer,
**	or, if we've reached the end of the file, the data element
**		will be removed from the list of file descriptors.
**
**	- data		list's element corresponding to the current file descriptor
**	- line		string to be filled with the buffer's content
** -------------------------------------------------------------------- */
static int	parse_buffer(t_listfd *data, char **line)
{
	size_t	start;

	start = data->index;
	while (data->index < data->size - 1 && data->buffer[data->index] != '\n')
		data->index++;
	data->index++;
	*line = realloc_line(*line, data->buffer + start, data->index - start);
	if (data->buffer[data->index - 1] == '\n')
		return (1);
	return (0);
}

/* -----------------------------------------------------------------------
 **		get_next_line
 **
 **	Returns the next line it can read in the file described by fd.
 **	Returns NULL in case there is no next line.
 **	The line-ending '\n' is included in the returned string.
 **
 **	Multiple file descriptors can be used interchangeably.
 **
 **	The functions work by manipulating a list containing an entry
 **		for each file descriptor opened so far.
 **	Each new file descriptor will be assigned an element in the list,
 **		which will contain all its relevant data such as its buffer.
 **
 **	A file descriptor will be freed and removed from the list when we've
 **		returned the last line in the file.
 **
 **	- fd		file descriptor to read from
 ** -------------------------------------------------------------------- */
char	*get_next_line(int fd)
{
	static t_listfd	*listfd = NULL;
	t_listfd		*data;
	char			*line;

	if (! gnl_lstseek(listfd, fd))
		gnl_lstadd(&listfd, fd);
	data = gnl_lstseek(listfd, fd);
	if (data->index == data->size)
	{
		data->size = read(data->fd, data->buffer, BUFFER_SIZE);
		data->index = 0;
	}
	line = NULL;
	while (data->size > 0)
	{
		if (parse_buffer(data, &line))
			return (line);
		data->size = read(data->fd, data->buffer, BUFFER_SIZE);
		data->index = 0;
	}
	gnl_lstdel(&listfd, data);
	return (line);
}
