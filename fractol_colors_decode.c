/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_colors_decode.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:20:27 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/22 23:07:50 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Returns how many colors are in our line
static int	get_color_count(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		if (*line)
			count++;
		while (ft_ishex(*line))
			line++;
	}
	return (count);
}

//	Fills an array of ints with color values read from
//		the given line
//	The array is freed in the parent function
static int	*get_colors(char *line, int color_count)
{
	int	*colors;
	int	size;

	size = 0;
	colors = malloc(color_count * sizeof(int));
	if (!colors)
		return (NULL);
	while (size < color_count)
	{
		while (ft_isspace(*line))
			line++;
		if (*line)
		{
			colors[size] = ft_atoi_base(line, BASE_16);
			size++;
		}
		while (ft_ishex(*line))
			line++;
	}
	return (colors);
}

/* --------------------------------------------------------------------- *\
|		create_palette
|
|	Creates and returns a complete palette featuring a gradient
|		between all colors given in our line string.
|
|	This palette is added to a chained list and freed when the
|		program ends.
|
|	Colors from the line are transformed into an array of ints
|		which get_gradient_palette can then use.
\* --------------------------------------------------------------------- */
int	*create_palette(char *line, int size)
{
	int		*palette;
	int		*colors;
	int		color_count;

	color_count = get_color_count(line);
	colors = get_colors(line, color_count);
	if (!colors)
		return (NULL);
	palette = get_gradient_palette(colors, color_count, size);
	free(colors);
	return (palette);
}
