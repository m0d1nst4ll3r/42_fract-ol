/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils_color2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 14:56:20 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/22 18:11:56 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//	Returns a value between color1 and color2
//	ratio should be between 0 and 1
int	get_gradient(int color1, int color2, float ratio)
{
	int	r;
	int	g;
	int	b;

	r = (get_r(color2) - get_r(color1)) * ratio + get_r(color1);
	g = (get_g(color2) - get_g(color1)) * ratio + get_g(color1);
	b = (get_b(color2) - get_b(color1)) * ratio + get_b(color1);
	return (r << 16 | g << 8 | b);
}

/* --------------------------------------------------------------------- *\
|		get_gradient_palette
|
|	Creates an array of colors (a palette) from another array of colors.
|
|	Colors are in 0xrrggbb form, transparency is ignored.
|
|	Takes in :
|		- colors		the base array of colors
|		- color_count	the size of that array
|		- size			the size of the new array
|
|	Each color of the base colors array is compared to the next one in
|		order to create a new intermediate color.
|
|	This is done over and over again to create gradients between each
|		pair of colors in the base colors array.
|
|	A pair of colors is always colors[i] and colors[i + 1], so the base
|		colors array cannot contain less than 2 colors.
|
|	Method and arithmetic for building the new palette :
|
|	- Our palette of [size] will be divided in sections of gradients
|		between pairs of colors
|	- Since we have [color_count] colors, we have [color_count] - 1 sections
|		SECTIONS = color_count - 1
|	- Each of these sections will take [size] / SECTIONS slots
|		SLOTS = size / (color_count - 1)
|		this number is a rational and not an integer, this will be resolved
|	- The number of slots each section takes is the number of different
|		colors present in each color-pair gradient
|	- Gradients use a ratio starting at 0 and ending at 1, so the amount by
|		which to increment our gradient ratio is 1 / SLOTS
|		RATIO_STEP = 1 / (size / (color_count - 1))
|	- If [size] is not a multiple of [color_count - 1], RATIO_STEP will not
|		add up nicely to 1, you might get 0.8 followed by 1.1, and a way to
|		resolve this nicely is to carry over this ratio - 1 difference to the
|		next color-pair ratio.
|	- Hence, ratio is continuous over all the color pairs.
|	- The last problem to resolve is how to start and end our palette
|		- We can start and end our palette with 0 and 1
|			Ex: 000000 808080 ffffff
|				0.00   0.50   1.00
|		- We can start and end with mid-values
|			Ex: 404040 808080 bfbfbf
|				0.25   0.50   0.75
|	- For the former, we simply start at 0 and substract 1 to [size]
|		RATIO_STEP = 1 / (size - 1 / (color_count - 1))
|	- For the latter, we start at an already incremented ratio and add 1
|		RATIO_STEP = 1 / (size + 1 / (color_count - 1))
\* --------------------------------------------------------------------- */
int	*get_gradient_palette(int *colors, int color_count, int size)
{
	int		*palette;
	int		i;
	int		j;
	float	ratio;
	float	ratio_step;

	palette = malloc(size * sizeof(int));
	if (! palette)
		return (NULL);
	ratio_step = 1 / (((float)size - 1) / ((float)color_count - 1));
	ratio = 0;
	i = 0;
	j = 0;
	while (i < size)
	{
		palette[i] = get_gradient(colors[j], colors[j + 1], ratio);
		ratio += ratio_step;
		if (ratio > 1)
		{
			ratio--;
			j++;
		}
		i++;
	}
	return (palette);
}
