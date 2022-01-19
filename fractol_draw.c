/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:01:07 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/19 15:57:38 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
static int	get_color_iter(t_fract data, float iter)
{
	int	color;

	if ((int)iter >= data.max_iter)
		color = 0;
	else if (!data.smoothcol)
		color = data.curcol->palette[(int)iter % data.curcol->palette_size];
	else
		color = get_gradient(
				data.curcol->palette[(int)iter % data.curcol->palette_size],
				data.curcol->palette[
				((int)iter + 1) % data.curcol->palette_size],
				iter - (int)iter);
	return (color);
}

static float	calculate_map_pixel(t_fract data, long double x, long double y)
{
	t_complex	variable;

	variable.x = x;
	variable.y = y;
	if (data.type == 'm')
		return (escape_time(data.constant, variable, data.max_iter));
	else
		return (escape_time(variable, data.constant, data.max_iter));
}

/* --------------------------------------------------------------------- *\
|		calculate_map
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
|
|	The resulting map is then used for coloring based on a palette.
\* --------------------------------------------------------------------- */
void	*calculate_map(void *arg)
{
	int			x;
	int			y;
	int			thread;
	t_fract		*data;

	data = (t_fract *)arg;
	pthread_mutex_lock(&(data->mutex));
	data->thread++;
	thread = data->thread;
	pthread_mutex_unlock(&(data->mutex));
	y = thread;
	while (y < data->winy)
	{
		x = -1;
		while (++x < data->winx)
		{
			if (data->highest_iter && (int)data->map[y][x] < data->highest_iter)
				continue ;
			data->map[y][x] = calculate_map_pixel(*data,
					data->pos.x + data->step * x, data->pos.y - data->step * y);
		}
		y += NUMTHREADS;
	}
	pthread_exit(EXIT_SUCCESS);
}

//	Uses the map of escape times in combination with
//		a palette to color the fractal
void	*draw_fractal(void *arg)
{
	int		x;
	int		y;
	int		color;
	int		thread;
	t_fract	*data;

	data = (t_fract *)arg;
	pthread_mutex_lock(&(data->mutex));
	data->thread++;
	thread = data->thread;
	pthread_mutex_unlock(&(data->mutex));
	y = thread;
	while (y < data->winy)
	{
		x = -1;
		while (++x < data->winx)
		{
			color = get_color_iter(*data, data->map[y][x]);
			pixel_put(data->img_temp, x, y, color);
		}
		y += NUMTHREADS;
	}
	pthread_exit(EXIT_SUCCESS);
}
