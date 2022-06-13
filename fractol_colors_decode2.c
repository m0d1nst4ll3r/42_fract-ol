/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_colors_decode2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:59:32 by rpohlen           #+#    #+#             */
/*   Updated: 2022/06/13 22:49:13 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Returns palette name from line, moves string ahead for later use
static char	*get_name(char **line)
{
	int		i;
	char	*name;

	while (ft_isspace(**line))
		(*line)++;
	i = 0;
	while ((*line)[i] != ' ' && ft_isprint((*line)[i]))
		i++;
	name = ft_strndup(*line, i);
	*line += i;
	return (name);
}

//	Returns palette size from line, moves string ahead for later use
static int	get_size(char **line)
{
	int	nb;

	while (ft_isspace(**line))
		(*line)++;
	nb = ft_atoi(*line);
	while (ft_isdigit(**line))
		(*line)++;
	return (nb);
}

/* --------------------------------------------------------------------- *\
|		create_color
|
|	Allocates a color element, filling its name, palette and palette_size
|		with the provided line.
|
|	Since there are several allocations throughout this function, we
|		have to make sure any failed malloc frees previous ones.
\* --------------------------------------------------------------------- */
void	create_color(char *line, t_color **lst)
{
	t_color		*color;

	color = malloc(sizeof(*color));
	if (!color)
		return ;
	color->name = get_name(&line);
	if (!color->name)
	{
		free(color);
		return ;
	}
	color->palette_size = get_size(&line);
	color->palette = create_palette(line, color->palette_size);
	if (!color->palette)
	{
		free(color->name);
		free(color);
		return ;
	}
	fractol_lstadd(lst, color);
}

/* --------------------------------------------------------------------- *\
|		decode_colors
|
|	Parses the colors config file (typically named colors.fract)
|		to fill a list of palettes.
|
|	Each element of a list contains the palette's name (e.g "galaxy"),
|		the palette's size (e.g 100),
|		and the palette's array of colors (in hex form e.g 084fe1)
|
|	Invalid lines are ignored - if no valid lines are found, returns a
|		NULL list to be handled later on.
\* --------------------------------------------------------------------- */
t_color	*decode_colors(char *file)
{
	t_color		*colors;
	char		*line;
	int			fd;

	fd = open(file, O_RDONLY);
	if (fd < 3)
	{
		print_error(ERR_BADFILE, file);
		return (default_color());
	}
	colors = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (is_valid_line(line))
			create_color(line, &colors);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (colors);
}

//	Quickly builds a default color in case the file was empty
//		or could not be read.
t_color	*default_color(void)
{
	t_color	*colors;

	colors = NULL;
	create_color("rainbow 108 ff0000 ffa500 ffff00 008000 0000ff \
4b0082 ee82ee ff0000\n", &colors);
	return (colors);
}
