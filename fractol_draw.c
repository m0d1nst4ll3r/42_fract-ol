/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:01:07 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/03 15:41:30 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* --------------------------------------------------------------------- *\
|		escape_time
|
|	Takes in a complex number [c] and a complex number [s]
|
|	[s] is our starting value, [c] is the constant we're adding
|
|	Iterates at maximum [depth] times, squaring the result of the last
|		iteration ([s] if first) and adding [c] to it
|
|	When the resulting complex number is farther than a radius of 2 from
|		the center of our complex numbers graph (0, 0), stop iterating
|	(this is calculated with pythagore's theorem)
|
|	The number of iterations we've reached is then returned to be used
|		for coloring
|
|	x2 and y2 are used to save on the number of multiplications
|	long doubles are used to reach the highest precision possible (e-22)
|
|	For the Mandelbrot set, s will always be 0, 0 and c will vary based
|		on the area of the set and the pixel transformations
|	For any Julia set, c will always be a set value and s will vary based
|		on the area of the set and the pixel transformations
\* --------------------------------------------------------------------- */
static int	escape_time(t_complex s, t_complex c, int depth)
{
	long double	x2;
	long double	y2;
	int			iter;

	x2 = 0;
	y2 = 0;
	iter = 0;
	while (x2 + y2 <= 4 && iter < depth)
	{
		s.y = c.y + (s.x + s.x) * s.y;
		s.x = c.x + x2 - y2;
		x2 = s.x * s.x;
		y2 = s.y * s.y;
		iter++;
	}
	return (iter);
}

/* --------------------------------------------------------------------- *\
|		get_color_iter
|
|	Returns a color based on the number of iterations a complex number
|		took to escape.
|
|	If the complex number didn't escape (it reached max iterations), the
|		color is black.
|
|	Otherwise, the color is taken from a palette of colors with the
|		number of iterations as the index. If the number is greater than
|		the palette allows, we just circle back to its beginning.
\* --------------------------------------------------------------------- */
static int	get_color_iter(int *palette, int palette_size,
			int iter, int max_iter)
{
	int	color;

	if (iter == max_iter)
		color = 0;
	else
		color = palette[iter % palette_size];
	return (color);
}

/* --------------------------------------------------------------------- *\
|		draw_pixel
|
|	Calculates the escape time of a complex number for a given pixel.
|	Then, calculates the color of the pixel based on that escape time.
|	Finally, updates the pixel's color on the buffered image.
\* --------------------------------------------------------------------- */
static void	draw_pixel(t_fract data, int x, int y, t_complex variable)
{
	int	iter;
	int	color;

	if (data.type == 'm')
		iter = escape_time(data.constant, variable, data.max_iter);
	else
		iter = escape_time(variable, data.constant, data.max_iter);
	color = get_color_iter(data.palette, data.palette_size,
			iter, data.max_iter);
	pixel_put(data.img_temp, x, y, color);
}

/* --------------------------------------------------------------------- *\
|		draw_fractal
|
|	For each pixel in an image, transforms that pixel into a complex number
|		and calculates how fast that complex number will escape a circle of
|		radius 2, centered at point (0, 0) of the complex numbers graph.
|
|	This is called an escape time algorithm and is the basis of drawing a
|		mandelbrot or julia set fractal.
|
|	data contains the starting, first pixel, top-left complex number, [pos],
|		initialized at the start of the program based on window size.
|	[pos] is then incremented for each pixel by [step] to update our complex
|		number. The bigger step is, the less zoomed-in the image.
|
|	We increment [pos] by [step] instead of multiplying it to save on
|		floating point multiplications. This causes image deformation when
|		approaching max long double precision.
\* --------------------------------------------------------------------- */
void	draw_fractal(t_fract data)
{
	int			x;
	int			y;
	t_complex	variable;

	variable.y = data.pos.y;
	y = 0;
	while (y < WIN_Y)
	{
		variable.x = data.pos.x;
		x = 0;
		while (x < WIN_X)
		{
			draw_pixel(data, x, y, variable);
			variable.x += data.step;
			x++;
		}
		variable.y -= data.step;
		y++;
	}
}