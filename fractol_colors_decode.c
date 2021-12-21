/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_colors_decode.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:20:27 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/21 19:35:20 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Skips spaces at beginning of line before palette name
//	Then, duplicates said name and returns the new string
static char	*get_name(char *line)
{
	int		i;

	i = 0;
	while (ft_isspace(*line))
		line++;
	while (*line != ' ' && ft_isprint(*line))
		i++;
	return (ft_strndup(line, i));
}

//	Skips spaces, name, and spaces after name
//	Then, atoi's the number and returns it
static int	get_size(char *line)
{
	while (ft_isspace(*line))
		line++;
	while (ft_isprint(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	return (ft_atoi(line));
}

static int	*create_palette()
{

}

void	create_color(char *line, t_color **lst)
{
	t_color		*elem;

	elem = malloc(sizeof(*elem));
	elem->name = get_name(line);
	elem->palette_size = get_size(line);
	elem->palette = create_palette(/*ahem*/);
	fractol_lstadd(lst, elem);
}

/* -----------------------------------------------------------------------
**		decode_colors
**
**	Parses the colors config file (typically named colors.fract)
**		to fill a list of palettes.
**
**	Each element of a list contains the palette's name (e.g "galaxy"),
**		the palette's size (e.g 100),
**		and the palette's array of colors
----------------------------------------------------------------------- */
t_color	*decode_colors(char *file)
{
	t_color		*colors;
	char		*line;
	int			fd;

	fd = open(file, O_RDONLY);
	if (fd < 3)
		return (NULL);
	colors = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (is_valid_line(line))
			create_color(line, &colors);
		free(line);
		line = get_next_line(fd);
	}
	return (colors);
}
