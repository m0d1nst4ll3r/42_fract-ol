/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:01:07 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/23 19:25:02 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
|		draw_mandelbrot
|
|	For each pixel of an image, a given starting point (as a complex number)
|		and a given floating point value with which to increment the complex
|		number each pixel...
|
|	...This function calculates the amount of squaring and adding operations
|		that can occur before the value gets out of a circle of radius 2
|		centered at point 0, 0...
|
|	...Starting at point 0, 0
|
|	The exact formula for iteration N is result(N-1)² + C
|		iteration 1 starts at (0, 0) + C
|		iteration 2 starts at C² + C
|
|	The resulting amount of iterations is then used to color the pixel
|		according to a palette of colors
|
|	cx and cy are used to save on multiplications
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

/* --------------------------------------------------------------------- *\
|		draw_julia
|
|	Does the exact same as draw_mandelbrot, but this time, starting from
|		a variable point depending on the pixel
|
|	The exact formula for iteration N is result(N-1)² + C
|		iteration 1 is S² + C
|		iteration 2 is (S² + C)² + C
|
|	The resulting amount of iterations is then used to color the pixel
|		according to a palette of colors
|
|	s is used to save on multiplications (we could otherwise describe the
|		complex number as posx + x * step and posy - y * step)
\* --------------------------------------------------------------------- */
void	draw_julia(t_fract data)
{
	int			x;
	int			y;
	t_complex	s;

	s.y = data.pos.y;
	y = 0;
	while (y < WIN_Y)
	{
		s.x = data.pos.x;
		x = 0;
		while (x < WIN_X)
		{
			pixel_put(data.img_temp, x, y,
				get_color_iter(data.palette, data.palette_size,
					escape_time(data.constant, s,
						data.max_iter), data.max_iter));
			s.x += data.step;
			x++;
		}
		s.y -= data.step;
		y++;
	}
}
